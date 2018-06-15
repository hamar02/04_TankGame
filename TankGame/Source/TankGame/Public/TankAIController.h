// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATank * GetControlledTank() const;
	ATank * GetPlayerTank() const;

	void BeginPlay() override;

	void Tick(float DeltaTime);

private:
	ATank * m_PlayerTank;
	ATank * m_ControlledTank;

};
