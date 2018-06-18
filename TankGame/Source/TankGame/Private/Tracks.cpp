// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Tracks.h"

UTracks::UTracks() {
	PrimaryComponentTick.bCanEverTick = true;
}



void UTracks::ApplySidewayForce()
{
	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();

	UStaticMeshComponent* root = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector correctionForce = (root->GetMass()*correctionAcceleration) / 2;
	root->AddForce(correctionForce);
}

void UTracks::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
	ApplySidewayForce();
	DriveTank();
	currentThrottle = 0;
}

void UTracks::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTracks::OnHit);

}

void UTracks::DriveTank()
{
	FVector ForceApplied = GetForwardVector()*currentThrottle*TrackMaxDrivingForce;
	FVector ForcedLocation = GetComponentLocation();
	UPrimitiveComponent* Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	Tank->AddForceAtLocation(ForceApplied, ForcedLocation);

}



void UTracks::SetThrottle(float Throttle) {
	currentThrottle = FMath::Clamp<float>(Throttle + currentThrottle, -1.f, 1.f);


}


