// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

// Tick
	//Super
	//AimTowardsCrosshair()

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;

	FVector HitLocation; //Out Parameter
	
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
	}
	

	// Get world location of linetrace through crosshair
	// If it hits the landscape
		//Tell Controlled Tank to aim at this poin.
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Player Controller begin play"));

	auto ControlledTank = GetControlledTank();

	if(ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possesed Tank Name: %s"), *(ControlledTank->GetName()));
	}

	else
	{
	UE_LOG(LogTemp, Error, TEXT("No Possesed Tank found"));
	}

	GetControlledTank();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);

	return true;
}