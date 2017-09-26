// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"
//#include "force"


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
	_launchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	_impactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_impactBlast->bAutoActivate = false;

	_explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	_collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	_launchBlast->Deactivate();
	_impactBlast->Activate();

	SetRootComponent(_impactBlast);
	_collisionMesh->DestroyComponent();
	_explosionForce->FireImpulse();

	UGameplayStatics::ApplyRadialDamage(this, 10.0f, GetActorLocation(), _explosionForce->Radius, UDynamicClass::StaticClass(), TArray<AActor*>());

	FTimerHandle timer;
	GetWorld()->GetTimerManager().SetTimer(timer, this, &AProjectile::OnTimerExpire, _destroyDelay, false);
}

void AProjectile::OnTimerExpire() {
	Destroy();
}

void AProjectile::Launch(float speed)
{
	_projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	_projectileMovement->Activate();
}

