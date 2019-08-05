// Copyright 2019 Agata Les, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent * AimCompRef);

private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &) const;
	bool GetLookVectorHitLocation(FVector & LookDirection, FVector & HitLocation) const;
	bool GetLookDirection(FVector2D & ScreenLocation, FVector & LookDirection) const;

	UPROPERTY(EditAnywhere, meta=(ClampMin=0.2f, ClampMax=0.8f))
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0.2f, ClampMax = 0.8f))
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;
};
