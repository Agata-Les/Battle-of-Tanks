// Copyright 2019 Agata Les, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Locked;

private:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = Firing, meta = (ClampMin = 2000.0f, ClampMax = 8000.0f))
	float LaunchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0.0;
};
