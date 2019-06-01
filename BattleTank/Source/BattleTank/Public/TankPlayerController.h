// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "BattleTank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"  ///Must be last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:


	virtual void BeginPlay() override;

	ATank* GetControlledTank() const;

	virtual void Tick(float DeltaSeconds) override;

	//Start moving tank barrel so that it aims where crosshair is
	//Pointed in the world.
	void AimTowardsCrosshair();
	
	bool GetSightRayHitLocation(FVector& OutHitlocation) const;
};
