// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NodeGameMode.generated.h"

class UBuffComponent;
class UZombieBuffComponent;
class APlantBase;
class AZombieBase;

/**
 * 
 */
UCLASS()
class PVZ_API ANodeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ANodeGameMode();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuffComponents")
	UBuffComponent* PlantBuffComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuffComponents")
	UZombieBuffComponent* ZombieBuffComponent;

	virtual void Init(UBuffComponent* PlantComponent, UZombieBuffComponent* ZombieComponent);

	//// 植物伤害计算
	//UFUNCTION(BlueprintCallable, Category = "DamageCalculation")
	//float CalculatePlantDamageOutput(float InDamage);

	//UFUNCTION(BlueprintCallable, Category = "DamageCalculation")
	//float CalculatePlantDamageTaken(float InDamage);

	//// 僵尸伤害计算
	//UFUNCTION(BlueprintCallable, Category = "DamageCalculation")
	//float CalculateZombieDamageOutput(float InDamage);

	//UFUNCTION(BlueprintCallable, Category = "DamageCalculation")
	//float CalculateZombieDamageTaken(float InDamage);
};
