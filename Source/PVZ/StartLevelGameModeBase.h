// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "StartLevelGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API AStartLevelGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStartLevelGameModeBase();

protected:
	virtual void BeginPlay() override;

private:
	
};
