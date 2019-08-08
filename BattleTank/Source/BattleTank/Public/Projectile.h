// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile(float Speed);

private:
	UProjectileMovementComponent * ProjectileMovement = nullptr;

	UPROPERTY(VIsibleAnywhere)
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VIsibleAnywhere)
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VIsibleAnywhere)
	UParticleSystemComponent* ImpactBlast = nullptr;
};
