// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:	
	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel* barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTankTurret* turret);

	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* _tankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* _tankMovementComponent = nullptr;
	
private:
	// Sets default values for this pawn's properties
	ATank();	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, category = Firing)
	float _launchSpeed = 10000;
	
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> _projectileBlueprint;

	UTankBarrel* _barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float _reloadTime = 3.f;

	double _lastFireTime = 0;
};
