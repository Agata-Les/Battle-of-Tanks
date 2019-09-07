// Copyright 2019 Agata Les, All Rights Reserved.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank controlleg by %s DIED"), *GetName())
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (!InPawn) return;
	auto Tank = Cast<ATank>(InPawn);

	if (!Tank) return;
	//Subscribe our local method to the tank's death event
	Tank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
}
