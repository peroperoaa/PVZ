// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZombieStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PVZ_API UZombieStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UZombieStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseAttackInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseCritRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseCritDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DataTable;

	//用于读取基础属性
	bool Init(int32 SelfZombieID);
		
};
