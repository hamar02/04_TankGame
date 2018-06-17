// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include"GameFramework/Actor.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringStates : uint8 {
	Reloading, Locked, Aiming
};

//
class UTankBarrel;
class UTankTurret;

// Hold barrel Parameters and Elevate Method
UCLASS(meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* Barrel, UTankTurret* Turret);

	// Sets default values for this component's properties
	UTankAimingComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStates state = EFiringStates::Reloading;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);

	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

private:
	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 10000;

	UTankBarrel * Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
