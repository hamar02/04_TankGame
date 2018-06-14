// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define OUT
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	ATank * GetControlledTank() const;
	
	void BeginPlay() override;
	void Tick(float DeltaTime);

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;


private:
	ATank * controlledTank;
};
