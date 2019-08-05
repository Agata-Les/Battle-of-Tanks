// Copyright 2019 Agata Les, All Rights Reserved.

#include "TankAIController.h"
#include "TankAimingComponent.h"
//Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	PossesedTank = GetPawn();

	if (!ensure(PossesedTank)) return;
	PossesedTankAimingComponent = PossesedTank->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ensure(PlayerTank) || !ensure(PossesedTank)) return;
	MoveToActor(PlayerTank, AcceptanceRadius);

	if (!ensure(PossesedTankAimingComponent)) return;
	PossesedTankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (PossesedTankAimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		PossesedTankAimingComponent->Fire();
	}
}
