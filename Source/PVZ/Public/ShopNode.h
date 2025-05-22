// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapNode.h"
#include "Components/WidgetComponent.h"
#include "ShopNode.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API AShopNode : public AMapNode
{
	GENERATED_BODY()

public:
	AShopNode();
	
	virtual void EnterNode_Implementation(APlayerController* PlayerController) override;
};
