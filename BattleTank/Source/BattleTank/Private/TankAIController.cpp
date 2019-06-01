// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	/*
	auto ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed AI Tank Name: %s"), *(ControlledTank->GetName()));
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Possessed AI Tanks Found!"));
	}
	*/

	auto PlayerTank = GetPlayerTank();

	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Player Tank Name: %s  Location: %s"), *(PlayerTank->GetName()), *(PlayerTank->GetActorLocation().ToString()));
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Possessed AI Tanks Found!"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	return Cast<ATank>(PlayerPawn);
}