// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrelStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrelStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

	UPROPERTY(EditAnywhere)
		float MinElevationDegrees = 0;
	UPROPERTY(EditAnywhere)
		float MaxElevationDegrees = 30;
	
	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 8;

};
