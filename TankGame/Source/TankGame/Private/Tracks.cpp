// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Tracks.h"


void UTracks::SetThrottle(float Throttle) {

	FVector ForceApplied = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	FVector ForcedLocation = GetComponentLocation();
	UPrimitiveComponent* Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(ForceApplied, ForcedLocation);

}


