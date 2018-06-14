// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"

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
	auto controlledTank = GetPlayerTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller cant find player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player %s"), *controlledTank->GetName());
	}

}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//
	UE_LOG(LogTemp, Warning, TEXT("AI controller is ticking"));

}
