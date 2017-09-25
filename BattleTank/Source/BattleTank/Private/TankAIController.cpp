// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
	UTankAimingComponent* aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (!ensure(player && aimingComponent)) { return; }

	MoveToActor(player, _acceptanceRadius);	
	aimingComponent->AimAt(player->GetActorLocation());

	if (aimingComponent->GetFiringState() == EFiringState::Locked) {
		aimingComponent->Fire();
	}
	
}
