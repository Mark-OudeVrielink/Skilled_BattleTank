// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"



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

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if(InPawn){
		auto possedTank = Cast<ATank>(InPawn);
		if (!ensure(possedTank)) { return; }
		//possedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

//void ATankAIController::OnTankDeath()
//{
//}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}
