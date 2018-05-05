// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> result = GetOwner()->GetComponentsByClass(UStaticMeshComponent::StaticClass());
	
	for (auto component : result)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Search: %s"), *component->GetName());
		if (component->GetName() == "Barrel")
		{
			Barrel = Cast<UTankBarrelStaticMeshComponent>(component);
			UE_LOG(LogTemp, Warning, TEXT("Barrel found!"));
		}
		if (component->GetName() == "Turret")
		{
			Turret = Cast<UStaticMeshComponent>(component);
			UE_LOG(LogTemp, Warning, TEXT("Turret found!"));
		}
	}
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

//void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
//{
//	if (BarrelToSet)
//		Barrel = BarrelToSet;
//}

void UTankAimingComponent::AimAt(const FVector& WorldSpaceAim, float LaunchSpeed)
{
	if (!Barrel) { return; }

	auto OurTankName = GetOwner()->GetName();

	FVector OutLauncherVelocity;
	FVector StartLocaltion = Barrel->GetSocketLocation("Projectile");

	if (UGameplayStatics::SuggestProjectileVelocity(this,
		OUT OutLauncherVelocity, StartLocaltion, WorldSpaceAim, LaunchSpeed,
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLauncherVelocity.GetSafeNormal();

		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		auto AimAsRotator = AimDirection.Rotation();
		auto DeltaRotator = AimAsRotator - BarrelRotator;

		Barrel->Elevate(DeltaRotator.Pitch);

		//UE_LOG(LogTemp, Log, TEXT("Output LaunchVelocity: %s"), *OutLauncherVelocity.ToString());
	}
	
}

UTankBarrelStaticMeshComponent* UTankAimingComponent::GetBarrel()
{
	return this->Barrel;
}

