// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector location, float launchSpeed)
{
	if (!_barrel) { return; }

	FVector launchVelocity;
	FVector startLocation = _barrel->GetSocketLocation(FName("BarrelEnd"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, launchVelocity, startLocation, location, launchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		FVector aimDirection = launchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("aiming at %s"), *aimDirection.ToString());
	}	
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * barrelToSet)
{
	_barrel = barrelToSet;
}

