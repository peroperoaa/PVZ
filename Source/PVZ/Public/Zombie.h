// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZombieBase.h"
#include "Components/CapsuleComponent.h"
#include "Zombie.generated.h"

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForABP")
	bool bIsNeedAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ForABP")
	bool bIsDead;

	virtual void Dead() override;

	virtual void BeginPlay() override;

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
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void Move(bool bIsMove);
};
