// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto player = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto controlledTank = Cast<ATank>(GetPawn());

	if (player) {

		controlledTank->AimAt(player->GetActorLocation());
		controlledTank->Fire();
	}
}
