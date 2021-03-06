// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, category = Setup)
	void Initialise(UTankTrack* leftTrack, UTankTrack* rightTrack);

	UFUNCTION(BlueprintCallable, category = Input)
	void IntendMoveForward(float throwAmount);
	
	UFUNCTION(BlueprintCallable, category = Input)
	void IntendTurnRight(float throwAmount);
private:

	UTankTrack* _leftTrack = nullptr;
	UTankTrack* _rightTrack = nullptr;

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed);
};
