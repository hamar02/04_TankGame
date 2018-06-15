// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define OUT
#include"Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

private:
	ATank * controlledTank;
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333;
	UPROPERTY(EditAnywhere)
		float LineTraceRange= 1000000;


	void BeginPlay() override;
	void Tick(float DeltaTime);

	void AimTowardsCrosshair();
	ATank * GetControlledTank() const;
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;



};
