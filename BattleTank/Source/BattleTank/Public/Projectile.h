// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

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
	void Launch(float speed);

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();
	
	UProjectileMovementComponent* _projectileMovement = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* _collisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent* _launchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent* _impactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	URadialForceComponent* _explosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float _destroyDelay = 1.0f;
};
