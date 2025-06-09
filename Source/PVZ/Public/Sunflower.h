// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlantBase.h"
#include "Sunflower.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API ASunflower : public APlantBase
{
	GENERATED_BODY()
public:

	ASunflower();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnCreateSunlight();
	//
	FTimerHandle CreateSunlightTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProductInterval;
	
	virtual void Dead() override;
};
