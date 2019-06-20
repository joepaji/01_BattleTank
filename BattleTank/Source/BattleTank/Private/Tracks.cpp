// Fill out your copyright notice in the Description page of Project Settings.


#include "Tracks.h"



void UTracks::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Throttle: %f"), *GetName(), Throttle);

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}