// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdAIController.h"
#include "Kismet/GameplayStatics.h"



void ABirdAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	SetFocus(PlayerPawn);


}

void ABirdAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);


	if(LineOfSightTo(PlayerPawn))
	{

		MoveToActor(PlayerPawn, 0);

	}


}