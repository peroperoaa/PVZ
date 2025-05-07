// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapNode.h"
#include "TreasureNode.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API ATreasureNode : public AMapNode
{
	GENERATED_BODY()
	
public:
	virtual void EnterNode_Implementation(APlayerController* PlayerController) override;
};
