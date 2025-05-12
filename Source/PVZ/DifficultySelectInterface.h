// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DifficultySelectInterface.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API UDifficultySelectInterface : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int32 Difficulty = 1;

	UFUNCTION(BlueprintCallable)
	void ScrollToDifficulty();

	UFUNCTION(BlueprintCallable)
	void SetDifficultyButtonForbid();

protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* AddDifficultyButton;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* DifficultySelectScrollBox;

	UPROPERTY(meta = (BindWidget))
	class UButton* MinusDifficultyButton;

	UFUNCTION()
	void AddDifficultyButtonClicked();

	UFUNCTION()
	void MinusDifficultyButtonClicked();

	
};
