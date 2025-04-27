// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlantPeashooterAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PVZ_API UPlantPeashooterAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlantPeashooterAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//攻击定时器
	FTimerHandle AttackTimerHandle;

	//炮弹类型
	TSubclassOf<AActor> AttackProjectileClass;

	//攻击间隔
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackInterval;

	//尝试攻击
	UFUNCTION(BlueprintCallable)
	void OnTryAttack();
};
