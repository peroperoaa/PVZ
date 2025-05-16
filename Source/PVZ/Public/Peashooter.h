// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlantBase.h"
#include "Peashooter.generated.h"

class APlantProjectileBase;
/**
 * 
 */
UCLASS()
class PVZ_API APeashooter : public APlantBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	APeashooter();

	//攻击定时器
	FTimerHandle AttackTimerHandle;

	//炮弹类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APlantProjectileBase> AttackProjectileClass;

	//攻击间隔
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackInterval;

	//尝试攻击，由蓝图实现
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnTryAttack();

};
