// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::MoveBarrel(FVector aimDirection)
{
	FRotator barrelRotator = _barrel->GetForwardVector().Rotation();
	FRotator aimRotator = aimDirection.Rotation();
	FRotator deltaRotator = aimRotator - barrelRotator;

	_barrel->Elevate(3);
}


void UTankAimingComponent::AimAt(FVector location, float launchSpeed)
{
	if (!_barrel) { return; }

	FVector launchVelocity;
	FVector startLocation = _barrel->GetSocketLocation(FName("BarrelEnd"));
	bool gotVelocity = UGameplayStatics::SuggestProjectileVelocity(this, launchVelocity, startLocation, location, launchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace);
		
	if(gotVelocity){		
		FVector aimDirection = launchVelocity.GetSafeNormal();	

		MoveBarrel(aimDirection);
	}	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * barrelToSet)
{
	_barrel = barrelToSet;
}

