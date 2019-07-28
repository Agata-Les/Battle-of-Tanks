// Copyright 2019 Agata Les, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void BeginPlay() override;

	//UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

protected:
	//UPROPERTY(BlueprintReadOnly)
	//UTankMovementComponent* TankMovementComponent = nullptr;

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category=Setup)
	void SetBarrelReference(UTankBarrel * BarrelToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing, meta = (ClampMin = 2000.0f, ClampMax = 8000.0f))
	float LaunchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UTankBarrel * Barrel = nullptr;

private:
	double LastFireTime = 0;
};
