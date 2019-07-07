// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	Barrel = FindComponentByClass<UTankBarrel>();
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	auto ProjectileSpawnLocation = Barrel->GetSocketLocation("Projectile");
	auto ProjectileSpawnRotation = Barrel->GetSocketRotation("Projectile");

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileSpawnLocation, ProjectileSpawnRotation);

	//	Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

	
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	//TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}