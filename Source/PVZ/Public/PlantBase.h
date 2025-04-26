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

//非抽象类植物需要为PlantID赋值，然后调用Init函数，并且必须重写Dead函数
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

	/*
		继承类无需配置
	*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperSpriteComponent* PaperSpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBuffComponent* BuffComponent;

	/*
		继承类需配置
	*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStateComponent* StateComponent;
	
	//需通过调用Init函数确保读取Statement血量，否则无法正常工作
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlantHealthBaseComponent* HealthComponent;

	//植物的ID，用于区分植物，且提供给StatementComponent在DataTable中读取数据
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PlantID;



	/*
		自身函数
	*/
	UFUNCTION(BlueprintCallable)
	virtual bool Init();

	UFUNCTION(BlueprintCallable)
	virtual void Dead() PURE_VIRTUAL(APlantBase::Dead, );

	/*
		封装自BuffComponent的函数
	*/

	//计算受到伤害
	UFUNCTION(BlueprintCallable)
	virtual float CalculateOutgoingDamage(float Damage);

	//计算对僵尸伤害
	UFUNCTION(BlueprintCallable)
	virtual float CalculateReceiveDamage(float Damage);

	//获取当前最大生命值，异常则返回-1
	UFUNCTION(BlueprintCallable)
	virtual float GetCurrentMaxHealth();

	//获取当前攻击冷却时间，异常则返回-1
	UFUNCTION(BlueprintCallable)
	virtual float GetCurrentAttackInterval();
};
