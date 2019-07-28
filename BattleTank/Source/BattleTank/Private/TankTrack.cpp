// Copyright 2019 Agata Les, All Rights Reserved.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
		//TODO Clamp actual throttle value 

	FVector Force = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector Location = GetComponentLocation();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(Force, Location);
}
