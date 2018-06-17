// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "../Public/Tank.h"

ATank* ATankAIController::GetControlledTank()const {
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(playerPawn);
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//
	ATank* playerTank = GetPlayerTank();
	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller cant find player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player %s"), *playerTank->GetName());
		m_PlayerTank = playerTank;
	}

	ATank* controlledTank = GetControlledTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller cant find player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player %s"), *controlledTank->GetName());
		m_ControlledTank = controlledTank;
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//
	if (m_PlayerTank) {
		MoveToActor(m_PlayerTank, AcceptanceRadius);
		m_ControlledTank->AimAt(m_PlayerTank->GetActorLocation());
		m_ControlledTank->Fire();
	}

}
