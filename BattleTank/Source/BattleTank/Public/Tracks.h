// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Tracks.generated.h"

/**
 * Tracks is used to set max driving force and apply forces to the tank
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTracks : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// Max driving force per track, in newtons.
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; /// Assume 48 ton tank, 1g force/10m/s^2 acceleration
};
