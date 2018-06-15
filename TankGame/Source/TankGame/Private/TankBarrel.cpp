// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	float DeltaElevation = FMath::Clamp<float>(RelativeSpeed,-1,1) * MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + DeltaElevation;
	float Elevation = FMath::Clamp<float>(NewElevation, MinDegrees, MaxDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}



