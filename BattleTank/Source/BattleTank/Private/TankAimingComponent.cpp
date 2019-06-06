// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;  // TODO Should this really tick? Tick function is commented down below.
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel || !Turret)
	{
		return;
	}
	

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed, 
		false, 
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
		);


	//Calculate the OutLaunchVelocity
	if (HaveAimSolution)
	{
		
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);

		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f - Aim Solution Found"), Time);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f - No Aim Solution Found"), Time);
	}


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work out difference between current barrel direction and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch); //TODO remove magic number

	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto TargetRotator = AimDirection.Rotation();
	auto TDeltaRotator = TargetRotator - TurretRotator;
	Turret->Rotate(TDeltaRotator.Yaw);
}

// Called every frame
// void UTankAimingComponent::TickComponent
// (
// 	float DeltaTime,
// 	enum ELevelTick TickType,
// 	FActorComponentTickFunction* ThisTickFunction
// )
// {
// 	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
// 
// }