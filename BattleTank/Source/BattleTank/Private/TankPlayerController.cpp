// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

#define OUT

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
	
	if (GetSightRayHitLocation(OUT HitLocation))
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
	///Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, OUT LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cross Hair position Deproject: %s"), *LookDirection.ToString())
	}
	
	

	//"De-project" the screen position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit (up to max range)
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; /// To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		OUT CameraWorldLocation, 
		OUT LookDirection);
}