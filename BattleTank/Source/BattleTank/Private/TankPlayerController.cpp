// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UTankAimingComponent* aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (!ensure(aimingComponent)) { return; }
	FoundAimingComponent(aimingComponent);	
}

void ATankPlayerController::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetPawn()) { return; }

	UTankAimingComponent* aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }
	
	FVector hitLocation; // out parameter.
	bool bGotHitSight = GetSightRayHitLocation(hitLocation);

	if (bGotHitSight) {
		aimingComponent->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & hitLocation) const
{	
	int32 viewportSizeX;
	int32 viewportSizeY;

	// Get the viewportsize.
	GetViewportSize(viewportSizeX, viewportSizeY);

	// Multiply the screensize with the crosshair loaction to get the true location on the screen.
	auto screenLocation = FVector2D(viewportSizeX * _crosshairPositionX, viewportSizeY * _crosshairPositionY);

	// "De-project" the crosshairs screen location into the world.
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection)) {
		return GetLookVectorHitLocation(lookDirection, hitLocation);		
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector & LookDirection) const
{
	FVector worldCameraLocation;
	
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldCameraLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector & hitLocation) const
{
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + lookDirection * _lineTraceRange;

	// If we hit something we set the hitLocation and return true; otherwise we return false.
	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility)) {
		hitLocation = hitResult.Location;
		return true;
	}
	return false;
}