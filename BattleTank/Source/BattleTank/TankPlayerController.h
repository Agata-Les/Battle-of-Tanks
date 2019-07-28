// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

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
