// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/Tank.h"
APawn* ATankAIController::GetControlledTank()const {
	return GetPawn();
}

APawn * ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return (playerPawn);
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//
	APawn* playerTank = GetPlayerTank();
	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller cant find player"));
	}
	else {
		m_PlayerTank = playerTank;
	}

	APawn* controlledTank = GetControlledTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller cant find player"));
	}
	else {
		m_ControlledTank = controlledTank;
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//
	if (!ensure(m_PlayerTank && m_ControlledTank)) {
		return;
	}

	MoveToActor(m_PlayerTank, AcceptanceRadius);

	UTankAimingComponent* aimingComponent = m_ControlledTank->FindComponentByClass<UTankAimingComponent>();
	aimingComponent->AimAt(m_PlayerTank->GetActorLocation());

	if (aimingComponent->GetFiringState() == EFiringStates::Locked) {
		aimingComponent->Fire();
	}
	
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	//
	if (InPawn) {
		ATank* PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }

		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
	}
}

void ATankAIController::OnPossesedTankDeath()
{
	if (!ensure(GetPawn())) {
		return;
	}

	GetPawn()->DetachFromControllerPendingDestroy();
}
