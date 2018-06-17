// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Tank.h"
#include "../Public/Projectile.h"
#include "../Public/TankBarrel.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//
}




void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;

	if (isReloaded && Barrel) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketLocation("FirePoint"), Barrel->GetSocketRotation("FirePoint"));
		//Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

}




