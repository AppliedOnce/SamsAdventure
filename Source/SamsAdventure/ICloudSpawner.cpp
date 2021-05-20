// Fill out your copyright notice in the Description page of Project Settings.


#include "ICloudSpawner.h"
#include "ICloud.h"


// Sets default values
AICloudSpawner::AICloudSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AICloudSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AICloudSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeAlive += DeltaTime;

	if (TimeAlive > TimeBetweenSpawn)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			for (int i = 0; i < 1; i++)
			{
				AICloud* icloud = World->SpawnActor<AICloud>(ICloudBlueprint, GetActorLocation() + ICloudSpawnPoint * i, GetActorRotation());

				if (icloud)
				{
					icloud->Spawner = this;
					UE_LOG(LogTemp, Log, TEXT("Cloud"));

					TimeAlive = 0.f;
				}
			}
		}
	}
}

