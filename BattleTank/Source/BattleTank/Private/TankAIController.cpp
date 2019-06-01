// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed AI Tank Name: %s"), *(ControlledTank->GetName()));
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
