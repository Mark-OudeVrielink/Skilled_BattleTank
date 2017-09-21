// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* _barrel = nullptr;
	UTankTurret* _turret = nullptr;	

	void MoveAim(FVector aimDirection);	

protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState _firingState = EFiringState::Reloading;

public:		
	UFUNCTION(BlueprintCallable, category = Setup)
	void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

	void AimAt(FVector location, float launchSpeed);		
};
