// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShooting.h"
#include "Bulletnut.h"
#include "BirdAIController.h"
#include "Kismet/GameplayStatics.h"



void AAIShooting::BeginPlay()
{
	Super::BeginPlay();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	SetFocus(PlayerPawn);


}

void AAIShooting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	

}