// Copyright 2019 Agata Les, All Rights Reserved.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("DONKEY: Tank.cpp Constructor"))
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: Tank.cpp BeginPlay"))
}

void ATank::AimAt(FVector HitLocation)
{
	//TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
	//TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::Fire()
{
	bool isReloaded = ( FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds );

	if (Barrel && isReloaded)
	{
		AProjectile * Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
