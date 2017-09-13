// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetControlledTank()) { return; }

}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}


