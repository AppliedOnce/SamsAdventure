// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseNut.h"

// Sets default values
ADefenseNut::ADefenseNut()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereCompoonent>(TEXT("Collider"));
	RootComponent = Collider;
}

// Called when the game starts or when spawned
void ADefenseNut::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefenseNut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

