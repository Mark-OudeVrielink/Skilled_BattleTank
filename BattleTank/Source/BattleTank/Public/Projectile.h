// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Launch(float speed);

private:
	
	UProjectileMovementComponent* _projectileMovement = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* _collisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent* _launchBlast = nullptr;
	
};
