// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZombieBase.h"
#include "Components/CapsuleComponent.h"
#include "Zombie.generated.h"


class APlantBase;
/**
 * 
 */
UCLASS()
class PVZ_API AZombie : public AZombieBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AZombie();

	//保存正在攻击的植物
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	APlantBase* AttackingPlant;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForABP")
	bool bIsNeedAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForABP")
	bool bIsDead;

	virtual void BeginPlay() override;

	virtual void Dead() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//攻击定时器
	FTimerHandle AttackTimerHandle;

	//攻击间隔
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackInterval;

	//尝试攻击，由蓝图实现
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnTryAttack();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnAttackingPlantDestroyed(AActor* DestroyedActor);

	UFUNCTION(BlueprintImplementableEvent)
	void Move(bool bIsMove);
};
