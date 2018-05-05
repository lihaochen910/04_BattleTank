// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::BeginPlay()
{
	controlledTank = GetControlledTank();

	if (!controlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("GetControlledTank == nullptr"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s controlled by AI"), *controlledTank->GetName());
	}

	playerTank = GetPlayerTank();

	if (!playerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("playerTank == nullptr"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("found player Tank: %s."), *playerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	if (!controlledTank || !playerTank) { return; }

	controlledTank->AimAt(playerTank->GetActorLocation());
}

