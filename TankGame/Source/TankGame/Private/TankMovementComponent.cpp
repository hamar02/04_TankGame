// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "../Public/Tracks.h"
void UTankMovementComponent::Initialise(UTracks* LTrack, UTracks* RTrack) {
	this->LTrack = LTrack;
	this->RTrack = RTrack;

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LTrack || !RTrack) { return; }
	LTrack->SetThrottle(Throw);
	RTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LTrack || !RTrack) { return; }
	LTrack->SetThrottle(Throw);
	RTrack->SetThrottle(-Throw);

}


