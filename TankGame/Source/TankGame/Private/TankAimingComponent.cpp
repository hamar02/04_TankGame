// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/Projectile.h"


void UTankAimingComponent::Initialise(UTankBarrel* Barrel, UTankTurret* Turret) {
	this->Barrel = Barrel;
	this->Turret = Turret;
}

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTime){
		firingState = EFiringStates::Reloading;
	}
	else if (IsBarrelMoving()) {
		firingState = EFiringStates::Aiming;
	}
	else if (Rounds <= 0) {
		firingState = EFiringStates::OutOfAmmo;
		Rounds = 0;
	}
	else {
		firingState = EFiringStates::Locked;
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBP)) { return; }

	

	if (firingState == EFiringStates::Locked || firingState == EFiringStates::Aiming) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketLocation("FirePoint"), Barrel->GetSocketRotation("FirePoint"));
		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		Rounds--;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation) {

	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	
	FVector outLaunchVelocity;
	FVector startLocation = Barrel->GetSocketLocation("FirePoint");
	
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		startLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		)
	) {
		AimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!ensure(Barrel ) || !ensure(Turret)) { return; }
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - TurretRotator;

	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);

	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);

	}
}

EFiringStates UTankAimingComponent::GetFiringState() const
{
	return firingState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return Rounds;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	FVector forward = Barrel->GetForwardVector();

	return !forward.Equals(AimDirection, 0.1f);
}

