// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieBase.generated.h"

class UPaperFlipbookComponent;
class UBoxComponent;
class UZombieStateComponent;
class UZombieBuffComponent;
class UPlantHealthBaseComponent;

//非抽象类僵尸构造函数中需要为ZombieID赋值，然后调用Init函数，并且必须在蓝图实现Dead函数
UCLASS()
class PVZ_API AZombieBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperFlipbookComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UZombieBuffComponent* BuffComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UZombieStateComponent* StateComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlantHealthBaseComponent* HealthComponent;

	//僵尸的ID，用于区分僵尸，且提供给ZombieStatementComponent在DataTable中读取数据
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ZombieID;


	/*
	自身函数
*/
	UFUNCTION(BlueprintCallable)
	virtual bool Init();

	//扣除生命值，传入伤害值
	UFUNCTION(BlueprintCallable)
	virtual void BeAttacked(float Damage);

	//死亡逻辑
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Dead();

	//添加奇物，需要再实现
	//UFUNCTION(BlueprintCallable)
	//virtual void AddBuff();

	//该函数会在AddBuff（添加奇物）中被调用，用于实现需要实时同步Buff组件中数值的新增组件的逻辑时重写(如attack组件中存储的实时攻击力需在此处更新，代码可参考AddBuff)
	//UFUNCTION(BlueprintCallable)
	//virtual void BuffUpdateOtherComponents();

	/*
		封装自ZombieBuffComponent的函数
	*/

	//计算对僵尸伤害,传入原始伤害，返回经过计算的伤害
	UFUNCTION(BlueprintCallable)
	virtual float CalculateOutgoingDamage(float Damage);

	/*
		封装自PlantHealthBaseComponent的函数
	*/

	//回复生命值，传入增加的生命值
	UFUNCTION(BlueprintCallable)
	virtual void AddHealth(float Value);

	//回复生命值百分比
	UFUNCTION(BlueprintCallable)
	virtual void AddHealthPercent(float Rate);

};
