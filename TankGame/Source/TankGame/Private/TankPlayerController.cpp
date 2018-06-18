// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankPlayerController.h"
#include "../Public/TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) {
		return;
	}
	FoundAimingComponent(aimingComponent);
	

}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }

	if (!ensure(aimingComponent)) { return; }

	FVector HitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation) {
		aimingComponent->AimAt(HitLocation);
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
		bool bVectorHit = GetWorld()->LineTraceSingleByChannel(hit, startLocation, endLocation, ECollisionChannel::ECC_Visibility);
		if (bVectorHit) {
			HitLocation = hit.ImpactPoint;
			return true;
		}
		else
		{
			HitLocation = FVector(0,0,0);
		}
	}
	return false;
}



