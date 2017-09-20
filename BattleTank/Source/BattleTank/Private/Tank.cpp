// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	_tankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::AimAt(FVector hitLocation)
{
	_tankAimingComponent->AimAt(hitLocation, _launchSpeed);	
}

void ATank::SetBarrel(UTankBarrel * barrel)
{
	_tankAimingComponent->SetBarrelReference(barrel);
	_barrel = barrel;
}

void ATank::SetTurret(UTankTurret* turret) {
	_tankAimingComponent->SetTurretReference(turret);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - _lastFireTime) > _reloadTime;

	if (_barrel && isReloaded) {
		auto projectile = GetWorld()->SpawnActor<AProjectile>(_projectileBlueprint, _barrel->GetSocketLocation(FName("BarrelEnd")), _barrel->GetSocketRotation(FName("BarrelEnd")));
		projectile->Launch(_launchSpeed);

		_lastFireTime = FPlatformTime::Seconds();
	}
//	UE_LOG(LogTemp, Warning, TEXT("Fireing"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

