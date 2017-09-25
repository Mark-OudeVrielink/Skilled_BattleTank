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
	Locked,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

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

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
	bool BarrelIsMoving();

	UPROPERTY(EditAnywhere, category = Firing)
	float _launchSpeed = 10000;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> _projectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float _reloadTime = 3.f;
		
	double _lastFireTime = 0;
	FVector _aimDirection;
	int _roundsLeft = 10;
protected:

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState _firingState = EFiringState::Reloading;
	
public:		
	UFUNCTION(BlueprintCallable, category = Setup)
	void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);
	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "State")
	int GetRoundsLeft() const;

	void AimAt(FVector hitLocation);
	EFiringState GetFiringState() const;
		
};
