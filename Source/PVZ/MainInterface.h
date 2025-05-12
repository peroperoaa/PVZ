// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainInterface.generated.h"
/**
 * 
 */
UCLASS()
class PVZ_API UMainInterface : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* NextStepButton;

	UPROPERTY(meta = (BindWidget)) 
	class UButton* PreviousStepButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UFUNCTION()
	void NextStepButtonClicked();

	UFUNCTION()
	void PreviousStepButtonClicked();
};	
