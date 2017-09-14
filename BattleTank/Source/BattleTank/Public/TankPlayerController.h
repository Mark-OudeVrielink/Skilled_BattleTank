// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	void AimTowardsCrosshair();

	virtual void Tick(float deltaTime) override;

	UPROPERTY(EditAnywhere)
	float _crosshairPositionX = 0.5f;
	UPROPERTY(EditAnywhere)
	float _crosshairPositionY = 0.333f;
	UPROPERTY(EditAnywhere)
	float _lineTraceRange = 100000.0f; // 10 Km.

	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const;

public:
	ATank* GetControlledTank() const;
	
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	
};
