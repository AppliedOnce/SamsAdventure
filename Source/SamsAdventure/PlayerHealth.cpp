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

void UPlayerHealth::ShieldPlayer()
{
	bIsShielded = true;
}

bool UPlayerHealth::CheckShielded()
{
	return bIsShielded;
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

void UPlayerHealth::LoseHp(float Amount)
{
	if (!bIsInvulnerable)
	{
		if (bIsShielded)
		{
			bIsShielded = false;
			bIsInvulnerable = true;
			return;
		}
		else
		{
			if (CurrentHealth <= 0.0f)
				CurrentHealth = 0.0f;
			else
				CurrentHealth -= Amount;

			bIsInvulnerable = true;
		}
	}
}

void UPlayerHealth::IncreaseHp(float Amount)
{
	if (CurrentHealth >= MaxHealth)
		CurrentHealth = MaxHealth;
	else
		CurrentHealth += Amount;
}

float UPlayerHealth::GetCurrentHp() const
{
	return CurrentHealth;
}

float UPlayerHealth::GetMaxHp() const
{
	return MaxHealth;
}