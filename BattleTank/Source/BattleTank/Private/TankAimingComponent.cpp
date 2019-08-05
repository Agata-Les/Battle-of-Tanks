// Copyright 2019 Agata Les, All Rights Reserved.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) return;
	if (!ensure(Turret)) return;

	FVector OutLaunchVelocity{ 0 };
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bIsLaunchVelocityFound =
		UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

	if (bIsLaunchVelocityFound)
	{
		AimDirectionSafeNormal = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirectionSafeNormal);
		MoveTurretTowards(AimDirectionSafeNormal);
	}
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (AmmoQuantity <= 0)
	{
		FiringStatus = EFiringStatus::NoAmmo;
	}
	else if (!IsReloaded)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if(IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto TurretRotator = Turret->GetComponentRotation();
	auto AimAsRotator = AimDirection.ToOrientationRotator();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	if (DeltaRotator.Yaw > 180.0f) DeltaRotator.Yaw = -(360.0f - DeltaRotator.Yaw);
	if (DeltaRotator.Yaw < -180.0f) DeltaRotator.Yaw = (360.0f + DeltaRotator.Yaw);

	Turret->Rotate(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;

	auto BarrelForwardVector = Barrel->GetForwardVector().GetSafeNormal();
	float Tolerance = 0.1f; //TODO Check tolerance if acceptable

	return !(BarrelForwardVector.Equals(AimDirectionSafeNormal, Tolerance));
}

void UTankAimingComponent::Fire()
{
	//if (AmmoQuantity <= 0) return;
	if (!ensure(Barrel && ProjectileBlueprint)) return;

	if (FiringStatus == EFiringStatus::Locked || FiringStatus == EFiringStatus::Aiming)
	{
		AProjectile * Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		if (!ensure(Projectile)) return;

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		AmmoQuantity--;
	
	}
}