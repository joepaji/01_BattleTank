// Fill out your copyright notice in the Description page of Project Settings.

#include "Tracks.h"
#include "TankMovementComponent.h"



void UTankMovementComponent::Initialize(UTracks* LeftTrackToSet, UTracks* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) return;
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	
	IntendMoveForward(ForwardThrow);
	IntendTurnRight(RightThrow);
	//	UE_LOG(LogTemp, Warning, TEXT("Tank Name: %s   Velocity: %s"), *TankName, *MoveVelocityString);
}