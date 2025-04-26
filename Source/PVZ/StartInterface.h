// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartInterface.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API UStartInterface : public UUserWidget
{
	GENERATED_BODY()
protected:
	// 重写Initialize函数
	virtual bool Initialize() override;

private:
	// 绑定按钮组件
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Adventure;

	// 定义一个点击事件的函数
	UFUNCTION()
	void Button_AdventureClicked();
};
