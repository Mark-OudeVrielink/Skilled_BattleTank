// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float _acceptanceRadius = 80000.0f;
	
	//UFUNCTION()
	//void OnTankDeath();
private:
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
	virtual void BeginPlay() override;
};
