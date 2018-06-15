// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	float DeltaRotation = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	float NewRotation = RelativeRotation.Yaw + DeltaRotation;
	//float Rotation = FMath::Clamp<float>(NewRotation, MinDegrees, MaxDegrees);
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}



