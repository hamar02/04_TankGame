// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class AProjectile;

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

public:	
	// Called every frame

private:
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTime = 5;
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBP = nullptr;

	UTankBarrel* Barrel = nullptr;
	float LastFireTime = 0;
};
