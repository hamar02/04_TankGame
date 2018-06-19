// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Tank.h"


float ATank::GetHealthPercentage()
{
	return CurrentHealthPoints/TotalHealthPoints;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealthPoints);

	CurrentHealthPoints -= DamageToApply;
	if (CurrentHealthPoints <= 0) {
		OnDeath.Broadcast();
	}
	return DamageToApply;
}









