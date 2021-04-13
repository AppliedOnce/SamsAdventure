// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealth.h"

// Sets default values for this component's properties
UPlayerHealth::UPlayerHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerHealth::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsInvulnerable)
	{
		Timer += DeltaTime;

		if (Timer >= InvulnerableSeconds)
		{
			UE_LOG(LogTemp, Warning, TEXT("No longer Invulnerable!"));
			bIsInvulnerable = false;
			Timer = 0.f;
		}
	}
}

void UPlayerHealth::LoseHp(int Amount)
{
	if (!bIsInvulnerable)
	{
		if (CurrentHealth <= 0)
			CurrentHealth = 0;
		else
			CurrentHealth -= Amount;

		bIsInvulnerable = true;
	}
}

void UPlayerHealth::IncreaseHp(int Amount)
{
	if (CurrentHealth >= MaxHealth)
		CurrentHealth = MaxHealth;
	else
		CurrentHealth += Amount;
}

int UPlayerHealth::GetCurrentHp() const
{
	return CurrentHealth;
}

int UPlayerHealth::GetMaxHp() const
{
	return MaxHealth;
}