// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float relativeSpeed) {
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);

	auto rotationChange = relativeSpeed * _MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewRotation = RelativeRotation.Yaw + rotationChange;

	SetRelativeRotation(FRotator(0, rawNewRotation, 0));
}


