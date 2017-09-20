// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public: 
	//Sets the throttle value for the given track.
	UFUNCTION(BlueprintCallable, Category = Input)
	FVector SetThrottle(float throttle);
	
private:
	//Max driving force in newtons applied per track.
	UPROPERTY(EditDefaultsOnly)
	float _maxDrivingforce = 40000.0f;
	
};
