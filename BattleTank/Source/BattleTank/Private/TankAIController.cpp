// Copyright 2019 Agata Les, All Rights Reserved.

#include "TankAIController.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#include "TankAimingComponent.h"


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto PossesedTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		//Moving
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Firing
		PossesedTank->AimAt(PlayerTank->GetActorLocation());
		Cast< UTankAimingComponent>(PossesedTank->GetComponentByClass(UTankAimingComponent::StaticClass()))->AimAt(PlayerTank->GetActorLocation(), PossesedTank->LaunchSpeed);

		PossesedTank->Fire();
	}
}
