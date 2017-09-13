// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetControlledTank()) { return; }


	FVector hitLocation; // out parameter.

	if (GetSightRayHitLocation(hitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("Hitlocation: %s") , *hitLocation.ToString());
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector & outHitLocation) const
{
	outHitLocation = FVector(1.0);
	return true;
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}


