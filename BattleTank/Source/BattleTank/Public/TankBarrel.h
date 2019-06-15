// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hideCategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);


private: 

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesElevation = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinDegreesElevation = 0.f; //Sensible Default

};
