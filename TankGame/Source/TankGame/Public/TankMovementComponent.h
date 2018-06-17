// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */

class UTracks;
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:
		UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendMoveForward(float Throw);
		UFUNCTION(BlueprintCallable, Category = "Input")
		void IntendTurnRight(float Throw);

		UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTracks * LTrack, UTracks * RTrack);
		virtual void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTracks* LTrack = nullptr;
	UTracks* RTrack = nullptr;


};
