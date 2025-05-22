// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapNode.h"
#include "WishNode.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API AWishNode : public AMapNode
{
	GENERATED_BODY()

public:
	AWishNode();
	
	virtual void EnterNode_Implementation(APlayerController* PlayerController) override;
};
