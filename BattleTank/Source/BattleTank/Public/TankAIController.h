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

private:
	APawn * PlayerTank = nullptr;
	APawn * PossesedTank = nullptr;

	UTankAimingComponent * PossesedTankAimingComponent = nullptr;

	float AcceptanceRadius = 100.0f;
};
