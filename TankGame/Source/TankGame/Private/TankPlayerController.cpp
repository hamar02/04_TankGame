// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankPlayerController.h"
#include "../Public/Tank.h"

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
		controlledTank->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation)const {

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);

	FVector CameraWorldLocation;
	FVector LookDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection)) {
		FHitResult hit;
		auto startLocation = PlayerCameraManager->GetCameraLocation();
		auto endLocation = startLocation + LookDirection * LineTraceRange;
		if (GetWorld()->LineTraceSingleByChannel(hit, startLocation, endLocation, ECollisionChannel::ECC_Visibility)) {
			HitLocation = hit.ImpactPoint;
		}
		else
		{
			HitLocation = FVector(0,0,0);
		}
	}
	return true;
}



