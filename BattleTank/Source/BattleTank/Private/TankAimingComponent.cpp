// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTankAimingComponent::BeginPlay() {
	_lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	if ((FPlatformTime::Seconds() - _lastFireTime) < _reloadTime) {
		_firingState = EFiringState::Reloading;
	}
	else if (BarrelIsMoving()) {
		_firingState = EFiringState::Aiming;
	}
	else {
		_firingState = EFiringState::Locked;
	}
}

void UTankAimingComponent::MoveAim(FVector aimDirection)
{
	if (!ensure(_barrel || _turret)) { return; }

	FRotator barrelRotator = _barrel->GetForwardVector().Rotation();
	FRotator aimRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimRotator - barrelRotator;

	_barrel->Elevate(deltaRotator.Pitch);
	if (FMath::Abs(deltaRotator.Yaw) > 180) {
		_turret->Rotate(deltaRotator.Yaw);
	}
	else {
		_turret->Rotate(-deltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::AimAt(FVector location)
{
	if (!ensure(_barrel)) { return; }

	FVector launchVelocity;
	FVector startLocation = _barrel->GetSocketLocation(FName("BarrelEnd"));
	bool gotVelocity = UGameplayStatics::SuggestProjectileVelocity(this, launchVelocity, startLocation, location, _launchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace);
		
	if(gotVelocity){		
		_aimDirection = launchVelocity.GetSafeNormal();	

		MoveAim(_aimDirection);		
	}	
}

void UTankAimingComponent::Fire()
{
	if (_firingState != EFiringState::Reloading) {
		if (!ensure(_barrel)) { return; }
		if (!ensure(_projectileBlueprint)) { return; }

		auto projectile = GetWorld()->SpawnActor<AProjectile>(_projectileBlueprint, _barrel->GetSocketLocation(FName("BarrelEnd")), _barrel->GetSocketRotation(FName("BarrelEnd")));
		projectile->Launch(_launchSpeed);

		_lastFireTime = FPlatformTime::Seconds();
	}
}

bool UTankAimingComponent::BarrelIsMoving() {
	FVector barrelForward = _barrel->GetForwardVector();
	return !barrelForward.Equals(_aimDirection, 0.5f);
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet) {
	_barrel = barrelToSet;
	_turret = turretToSet;
}