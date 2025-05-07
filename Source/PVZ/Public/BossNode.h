// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapNode.h"
#include "BossNode.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API ABossNode : public AMapNode
{
	GENERATED_BODY()
	
public:
	virtual void EnterNode_Implementation(APlayerController* PlayerController) override;
};
