// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#define OUT
#include"Engine/World.h"
#include "CoreMinimal.h"
#include"GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent * AimingComponentRef);
	
private:
	UTankAimingComponent * aimingComponent=nullptr;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333;
	UPROPERTY(EditAnywhere)
		float LineTraceRange= 1000000;

	virtual void SetPawn(APawn* InPawn)override;


	void BeginPlay() override;
	void Tick(float DeltaTime);

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;


	UFUNCTION()
		void OnPossesedTankDeath();
};
