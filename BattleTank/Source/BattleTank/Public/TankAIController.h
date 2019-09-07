// Copyright 2019 Agata Les, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTankDeath();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 2000.0f;

private:
	APawn * PlayerTank = nullptr;
	APawn * PossesedTank = nullptr;

	//Method called when possessing a pawn
	virtual void SetPawn(APawn* InPawn) override;

	UTankAimingComponent * PossesedTankAimingComponent = nullptr;
};
