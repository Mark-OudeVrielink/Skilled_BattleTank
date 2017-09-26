// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankMovementComponent.h"
#include "Projectile.h"


float ATank::GetHealthPercentage()
{
	return (float)_currentHealth/ (float)_startingHealth;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor* DamageCauser) {
	int damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int damageToApply = FMath::Clamp(damagePoints, 0 ,_currentHealth);

	_currentHealth -= damageToApply;

	if (_currentHealth <= 0) {
		//OnDeath.BroadCast();
	}

	return damageToApply;
}