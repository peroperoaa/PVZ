// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NodeGameMode.generated.h"

class UBuffComponent;
class UZombieBuffComponent;
class APlantBase;
class AZombieBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSunlightChanged, int32, NewSunlight);

/**
 * 
 */
UCLASS()
class PVZ_API ANodeGameMode : public AGameModeBase
{
	GENERATED_BODY()

	int32 CurrentSunlight;

	// 辅助函数，用于设置阳光并广播事件
	void SetSunlight(int32 NewAmount);

public:

	ANodeGameMode();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuffComponents")
	UBuffComponent* PlantBuffComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BuffComponents")
	UZombieBuffComponent* ZombieBuffComponent;

	virtual void Init(UBuffComponent* PlantComponent, UZombieBuffComponent* ZombieComponent);

	// 获取当前阳光数量的函数
	UFUNCTION(BlueprintPure, Category = "Game State")
	int32 GetCurrentSunlight() const;

	// 增加阳光数量的函数
	UFUNCTION(BlueprintCallable, Category = "Game State")
	void AddSunlight(int32 Amount);

	// 消耗阳光数量的函数
	UFUNCTION(BlueprintCallable, Category = "Game State")
	bool ConsumeSunlight(int32 AmountToConsume);

	// 当阳光数量改变时广播的委托实例
	UPROPERTY(BlueprintAssignable, Category = "Game Events")
	FOnSunlightChanged OnSunlightChangedDelegate;

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
