// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage();

	FTankDelegate OnDeath;
private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TotalHealthPoints = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealthPoints = TotalHealthPoints;


	ATank();

};
