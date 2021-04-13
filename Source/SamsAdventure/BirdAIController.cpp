// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdAIController.h"
#include "Kismet/GameplayStatics.h"

<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
void ABirdAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	SetFocus(PlayerPawn);
<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
}

void ABirdAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	MoveToActor(PlayerPawn, 0);
<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
}