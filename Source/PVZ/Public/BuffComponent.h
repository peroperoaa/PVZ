// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PVZ_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//额外攻击力数值加成
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

	//攻速
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeedRate;

	//百分比减伤
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageReductionRate;
	
	//额外暴击率加成
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExtraCritRate;

	//额外暴击伤害加成
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExtraCritDamage;

	//计算Buff数值
	UFUNCTION(BlueprintCallable)
	void CalculateBuffValue();

	//计算伤害数值
	UFUNCTION(BlueprintCallable)
	float CalculateAttackValue(float BaseAttack);


};
