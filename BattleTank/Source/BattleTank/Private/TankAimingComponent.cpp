// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!ensure(Barrel && Turret)){	return;	}
	

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
	}

// 	else
// 	{
// 		auto Time = GetWorld()->GetTimeSeconds();
// 		UE_LOG(LogTemp, Warning, TEXT("%f - No Aim Solution Found"), Time);
// 	}


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }
	// Work out difference between current barrel direction and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch); 

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