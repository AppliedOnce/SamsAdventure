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

	UPROPERTY(VisibleAnywhere, Category = "Health");
	float CurrentHealth{ 3.0f };

	UPROPERTY(EditAnywhere, Category = "Health");
	float MaxHealth{ 3.0f };

	UPROPERTY(EditAnywhere, Category = "Invulnerability");
	float InvulnerableSeconds{ 1.f };

	UPROPERTY(VisibleAnywhere, Category = "Invulnerability");
	bool bIsInvulnerable{ false };

	UPROPERTY(VisibleAnywhere, Category = "Invulnerability");
	bool bIsShielded{ false };

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void LoseHp(float Amount);
	UFUNCTION(BlueprintCallable)
	void IncreaseHp(float Amount);
	UFUNCTION(BlueprintCallable)
	float GetCurrentHp() const;
	UFUNCTION(BlueprintCallable)
	float GetMaxHp() const;
	void ShieldPlayer();
	bool CheckShielded();

	bool death = false;
private:

	float Timer{ 0.f };
};
