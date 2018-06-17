// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	APawn * GetControlledTank() const;
	APawn * GetPlayerTank() const;

	void BeginPlay() override;

	void Tick(float DeltaTime);

private:
	APawn * m_PlayerTank;
	APawn * m_ControlledTank;

	float AcceptanceRadius = 3000;
};
