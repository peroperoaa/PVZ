// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapNode.h"
#include "CombatNode.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API ACombatNode : public AMapNode
{
	GENERATED_BODY()

public:
	ACombatNode();
	
	virtual void EnterNode_Implementation(APlayerController* PlayerController) override;	
};
