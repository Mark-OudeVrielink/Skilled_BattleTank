// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {	
}

void UTankTrack::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	ApplySidewaysForce();
	_currentThrottle = 0.0f;
}

void UTankTrack::ApplySidewaysForce()
{
	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto deltaTime = GetWorld()->GetDeltaSeconds();
	FVector accelerationCorrection = -slippageSpeed / deltaTime * GetRightVector();

	UStaticMeshComponent* tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (tankRoot->GetMass() * accelerationCorrection) / 2;

	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle) {
	_currentThrottle = FMath::Clamp<float>(_currentThrottle + throttle, -1, 1);
}

void UTankTrack::DriveTrack() {
	FVector forceApplied = GetForwardVector() * _currentThrottle * _maxDrivingforce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, forceLocation);	
}


