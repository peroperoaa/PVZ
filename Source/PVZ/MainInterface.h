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
public:
	UPROPERTY(BlueprintReadWrite)
	int32 FertilizerNum = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 Money = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 CollectionNum = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 SelectedDifficulty = 1;

	UPROPERTY(BlueprintReadWrite)
	FString SelectedTeam;

	UFUNCTION()
	void SetNextStepButtonEnable();

	UFUNCTION()
	void UpdateAttire(UAttire* AddingAttire);

protected:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* NextStepButton;

	UPROPERTY(meta = (BindWidget)) 
	class UButton* PreviousStepButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UCollectionInterface* UI_CollectionInterface;

	UPROPERTY(meta = (BindWidget))
	class UButton* CollectionInterfaceButton;

	UFUNCTION()
	void NextStepButtonClicked();

	UFUNCTION()
	void PreviousStepButtonClicked();

	UFUNCTION()
	void CollectionInterfaceButtonClicked();

	

	UPROPERTY()
	int32 SwitcherChlidNum = 4;
};	
