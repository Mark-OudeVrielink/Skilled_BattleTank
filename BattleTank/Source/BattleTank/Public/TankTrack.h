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
	void DriveTrack();
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float throttle);
	
private:
	UTankTrack();

	virtual void BeginPlay() override;
	
	void ApplySidewaysForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,FVector NormalImpulse, const FHitResult& Hit);
	//Max driving force in newtons applied per track.
	UPROPERTY(EditDefaultsOnly)
	float _maxDrivingforce = 40000.0f;
	float _currentThrottle = 0.0f;
	
};
