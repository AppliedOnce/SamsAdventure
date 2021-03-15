// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHealth.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMSADVENTURE_API UPlayerHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void LoseHp(int ammount);
	void IncreaseHp(int ammount);
	int GetCurrentHp();
private:
	UPROPERTY(VisibleAnywhere, Category = "Health");
	int CurrentHealth{ 3 };

	UPROPERTY(EditAnywhere, Category = "Health");
	int MaxHealth{ 3 };

	UPROPERTY(EditAnywhere, Category = "Invulnerability");
	float InvulnerableSeconds{ 1.f };

	UPROPERTY(VisibleAnywhere, Category = "Health");
	bool bIsInvulnerable{ false };

	float Timer{ 0.f };
};
