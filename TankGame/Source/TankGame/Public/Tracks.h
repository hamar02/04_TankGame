// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Tracks.generated.h"

/**
 * Tank Track is used to set maximum driving force and to apply forces to tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000;

private:
	UTracks();


	void ApplySidewayForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	virtual void BeginPlay() override;

	void DriveTank();


	float currentThrottle = 0;
};
