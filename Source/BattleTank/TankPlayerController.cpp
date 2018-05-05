// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("GetControlledTank == nullptr"));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	//UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController tick(%f)"), DeltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ControlledTank) { return; }

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *HitLocation.ToString());
	} 

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;

	if (GetLookDireciton(ScreenLocation, OUT LookDirection) && GetLookVectorHitLocation(LookDirection, OUT OutLocation))
	{
		return true;
	}

	return false;
}

bool ATankPlayerController::GetLookDireciton(const FVector2D& ScreenLocation, FVector& LookDirection) const
{
	FVector WorldPosition;

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldPosition, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}
