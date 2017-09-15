// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::MoveAim(FVector aimDirection)
{
	FRotator barrelRotator = _barrel->GetForwardVector().Rotation();
	FRotator aimRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimRotator - barrelRotator;

	_barrel->Elevate(deltaRotator.Pitch);
	_turret->Rotate(deltaRotator.Yaw);
}

void UTankAimingComponent::AimAt(FVector location, float launchSpeed)
{
	if (!_barrel) { return; }

	FVector launchVelocity;
	FVector startLocation = _barrel->GetSocketLocation(FName("BarrelEnd"));
	bool gotVelocity = UGameplayStatics::SuggestProjectileVelocity(this, launchVelocity, startLocation, location, launchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace);
		
	if(gotVelocity){		
		FVector aimDirection = launchVelocity.GetSafeNormal();	

		MoveAim(aimDirection);		
	}	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * barrelToSet)
{
	if (!barrelToSet) { return; }
	_barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet) 
{
	if (!turretToSet) { return; }
	_turret = turretToSet;
}

