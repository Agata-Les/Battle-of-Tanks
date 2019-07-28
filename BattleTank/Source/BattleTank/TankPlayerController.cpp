// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"

#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* PossesedTank = GetControlledTank();

	if (PossesedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller possesing %s"), *PossesedTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller active but not possesing a tank."));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		Cast< UTankAimingComponent>( GetControlledTank()->GetComponentByClass(UTankAimingComponent::StaticClass()))->AimAt(HitLocation, GetControlledTank()->LaunchSpeed);
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
