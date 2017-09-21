// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrack, UTankTrack* rightTrack) {

	if (!leftTrack || !rightTrack) { return; }
	_leftTrack = leftTrack;
	_rightTrack = rightTrack;
}


void UTankMovementComponent::IntendMoveForward(float throwAmount) {
	_leftTrack->SetThrottle(throwAmount);
	_rightTrack->SetThrottle(throwAmount);
}

void UTankMovementComponent::IntendTurnRight(float throwAmount) {
	_leftTrack->SetThrottle(throwAmount);
	_rightTrack->SetThrottle(-throwAmount);
}

// Method taken from the engine and overriden.
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto aiForwardIntention = MoveVelocity.GetSafeNormal();

	float forwardThrow = FVector::DotProduct(tankForward, aiForwardIntention);
	float rightThrow = FVector::CrossProduct(tankForward, aiForwardIntention).Z;


	IntendMoveForward(forwardThrow);
	IntendTurnRight(rightThrow);
	//UE_LOG(LogTemp, Warning, TEXT(" vectoring to "));
}
