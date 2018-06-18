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
	Reloading, Locked, Aiming, OutOfAmmo
};

//
class UTankBarrel;
class UTankTurret;
class AProjectile;

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

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStates firingState = EFiringStates::Reloading;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);

	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	EFiringStates GetFiringState()const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft()const;

private:
	FVector AimDirection;
	UTankBarrel * Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 10000;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTime = 5;
	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBP = nullptr;

	float LastFireTime = 0;

	float Rounds = 5;
	bool IsBarrelMoving();
};
