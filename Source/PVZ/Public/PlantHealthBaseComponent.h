// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlantHealthBaseComponent.generated.h"

class UStateComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PVZ_API UPlantHealthBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlantHealthBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//当前生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealth;

	//经过计算后的最大生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CalculatedMaxHealth;

	//更新当前最大生命值
	UFUNCTION(BlueprintCallable)
	virtual void SetCurrentMaxHealth(float NewMaxHealth);

	//处理被攻击扣血逻辑，传入最终伤害值
	UFUNCTION(BlueprintCallable)
	virtual void BeAttacked(float FinalDamage);

	//回复生命值，传入增加的生命值
	UFUNCTION(BlueprintCallable)
	virtual void AddHealth(float Value);

	//初始化Health组件，返回是否初始化成功
	UFUNCTION(BlueprintCallable)
	virtual bool Init(UStateComponent* SelfStateComponent);

	//回复生命值百分比
	UFUNCTION(BlueprintCallable)
	virtual void AddHealthPercent(float Rate);
};
