// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	_projectileMovement->bAutoActivate = false;

	_collisionMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(_collisionMesh);
	_collisionMesh->SetNotifyRigidBodyCollision(true);
	_collisionMesh->SetVisibility(false);

	_launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	_launchBlast->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::Launch(float speed)
{
	_projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	_projectileMovement->Activate();
}

