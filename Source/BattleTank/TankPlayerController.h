// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "TankPlayerController.generated.h"	// Must be th last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void AimTowardsCrosshair();

private:
	ATank * ControlledTank;

	bool GetSightRayHitLocation(FVector& OutLocation);

	bool GetLookDireciton(const FVector2D& ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 100000;
};
