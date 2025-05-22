// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapNode.h"
#include "EncounterNode.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API AEncounterNode : public AMapNode
{
	GENERATED_BODY()
public:
	AEncounterNode();
	
	virtual void EnterNode_Implementation(APlayerController* PlayerController) override;
};
