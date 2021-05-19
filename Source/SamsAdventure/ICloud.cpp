// Fill out your copyright notice in the Description page of Project Settings.


#include "ICloud.h"
#include "ICloudSpawner.h"

// Sets default values
AICloud::AICloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	RootComponent = OurVisibleComponent;
}

// Called when the game starts or when spawned
void AICloud::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AICloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimePresent += DeltaTime;


	if (TimePresent > TimeToGetToTheOtherSide)
	{
		this->Destroy();
	}

	FVector NewLocation = GetActorLocation();
	NewLocation += -GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(NewLocation, false);
}

