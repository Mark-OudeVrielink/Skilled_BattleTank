// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

FVector UTankTrack::SetThrottle(float throttle) {
	//UE_LOG(LogTemp, Warning, TEXT("Throttle: %f"), throttle);

	
	//FVector forceApplied = GetForwardVector() * throttle * _maxDrivingforce;

	// Code from Tutorial video that somehow does not want to compile, so I used bp to fix the problem.
	//auto forceLocation = GetComponentLocation();
	//auto root = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		
	//root->AddforceAtLocation(forceApplied, forceLocation);
	//AddForce(forceApplied);
	
	return GetForwardVector() * throttle * _maxDrivingforce;
}


