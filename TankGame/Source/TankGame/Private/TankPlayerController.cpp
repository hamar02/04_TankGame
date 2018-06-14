// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank()const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//
	controlledTank = GetControlledTank();
	if (!controlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller is possesing %s"), *controlledTank->GetName());
	}

}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//
	UE_LOG(LogTemp, Warning, TEXT("Player controller is ticking"));
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!controlledTank) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"),*HitLocation.ToString());

	}

}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation)const {

	HitLocation = FVector(1, 1, 1);
	return true;
}
