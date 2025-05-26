// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZombieBuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PVZ_API UZombieBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UZombieBuffComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//额外最大生命值加成
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExtraMaxHealth;

	//额外攻击力数值加成
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExtraAttack;

	//攻击百分比加成
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRate;

	//额外防御力数值加成
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExtraDefense;

	//百分比减伤
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageReductionRate;

	//额外暴击率加成
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExtraCritRate;

	//额外暴击伤害加成
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExtraCritDamage;

	//移速加成
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExtraMoveSpeed;

	//计算Buff组件数值,需要再实现
	//UFUNCTION(BlueprintCallable)
	//void CalculateBuffValue();

	//计算伤害数值，一般由PlantBase调用，异常返回Damage
	UFUNCTION(BlueprintCallable)
	virtual float CalculateOutgoingDamage(float Damage);

	//计算受到伤害,一般由PlantBase调用，异常返回Damage,防御力减伤公式为x/(x + 600)，其中x为防御力
	UFUNCTION(BlueprintCallable)
	virtual float CalculateReceiveDamage(float Damage);

	//获取当前最大生命值，异常则返回-1
	UFUNCTION(BlueprintCallable)
	virtual float GetCurrentMaxHealth(float InMaxHealth);

	//获取当前攻击冷却时间，异常则返回-1，需要在实现
	UFUNCTION(BlueprintCallable)
	virtual float GetCurrentAttackInterval(float BaseAttackInterval);

	//传入奇物，需要再实现
	//UFUNCTION(BlueprintCallable)
	//virtual void AddBuff();
};
