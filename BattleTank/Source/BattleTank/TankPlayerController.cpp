// Copyright 2019 Agata Les, All Rights Reserved.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank controlleg by %s DIED"), *GetName())
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (!InPawn) return;
	auto Tank = Cast<ATank>(InPawn);

	if (!Tank) return;
	//Subscribe our local method to the tank's death event
	Tank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FVector HitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);


	if (bGotHitLocation)
	{
		if( !GetPawn() ) return;

		auto TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (ensure(TankAimingComponent))
		{
			TankAimingComponent->AimAt(HitLocation);
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = { CrossHairXLocation * ViewportSizeX , CrossHairYLocation * ViewportSizeY };

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	const FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	const FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel
		(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility
		))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D & ScreenLocation, FVector & LookDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		LookDirection);
}
