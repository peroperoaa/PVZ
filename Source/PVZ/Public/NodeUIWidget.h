// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapNode.h"
#include "RoguelikeMapManager.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "NodeUIWidget.generated.h"

/**
 * 节点UI控件，用于显示节点信息并提供交互功能
 */
UCLASS()
class PVZ_API UNodeUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// UI组件
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* NodeCanvas;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ActionButton;
    
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NodeInfoText;
	
};