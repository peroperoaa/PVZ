// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelMessageManageComponent.generated.h"

class APlantBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PVZ_API ULevelMessageManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelMessageManageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//处理植物信息
	TArray<APlantBase*> PlantMap[5][9];

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//检查植物是否可以放置
	UFUNCTION(BlueprintCallable)
	void CheckLocation(int32 Row, int32 Column, APlantBase* Plant);

	//添加植物信息
	UFUNCTION(BlueprintCallable)
	void AddPlant(int32 Row, int32 Column, APlantBase* Plant);

	//删除植物信息
	UFUNCTION(BlueprintCallable)
	void RemovePlant(int32 Row, int32 Column, APlantBase* Plant);


	UBuffComponent*

};
