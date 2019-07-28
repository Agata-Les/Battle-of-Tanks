// Copyright 2019 Agata Les, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveRight(float Throw);

private:
	//Called from the Pathfinding Logic by the AI Controller
	//Inherited from NavMeshComponent
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack * LeftTrack = nullptr;
	UTankTrack * RightTrack = nullptr;

	// TODO Set local variable for the Throttle and consume this variable every frame to prevent double-speed
	// while using Fly-By-Wire and direct steering the tracks at the same time. 
};
