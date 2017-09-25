// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	void AimTowardsCrosshair();

	UPROPERTY(EditAnywhere)
	float _crosshairPositionX = 0.5f;
	UPROPERTY(EditAnywhere)
	float _crosshairPositionY = 0.333f;
	UPROPERTY(EditAnywhere)
	float _lineTraceRange = 100000.0f; // 10 Km.

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;

protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* aimCompRef);
	
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	
};
