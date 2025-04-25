// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "PlantBase.generated.h"

class UStateComponent;
class UBuffComponent;
class UPlantHealthBaseComponent;
class UPlantAttackBaseComponent;
class UPaperSpriteComponent;

//PlantBase类型没有用CreatDefaultSubobject给UStateComponent和UPlantHealthBaseComponent和UPlantAttackBaseComponent赋值，为nullptr，子类中请赋值
UCLASS(Abstract)
class PVZ_API APlantBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStateComponent* StateComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBuffComponent* BuffComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlantHealthBaseComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlantAttackBaseComponent* AttackComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperSpriteComponent* PaperSpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PlantID;

	//计算受到伤害
	UFUNCTION(BlueprintCallable)
	virtual float CalculateOutgoingDamage(float Damage);

	//计算对僵尸伤害
	UFUNCTION(BlueprintCallable)
	virtual float CalculateReceiveDamage(float Damage);

	//获取当前最大生命值，异常则返回-1
	UFUNCTION(BlueprintCallable)
	float GetCurrentMaxHealth();

	//获取当前攻击冷却时间，异常则返回-1
	UFUNCTION(BlueprintCallable)
	float GetCurrentAttackInterval();
};
