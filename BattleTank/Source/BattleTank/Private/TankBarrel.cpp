// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed) {
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);

	auto elevationChange = relativeSpeed * _MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = FMath::Clamp<float>(RelativeRotation.Pitch + elevationChange, _MinElevationDegrees, _MaxElevationDegrees);

	SetRelativeRotation(FRotator(rawNewElevation, 0,0));		
}



