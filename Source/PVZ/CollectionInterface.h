// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attire.h"
#include "Blueprint/UserWidget.h"
#include "CollectionInterface.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API UCollectionInterface : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetDisplayInfo(const FAttireInfo& AttireInfo);

	UFUNCTION(BlueprintCallable)
	void UpdateAttire(int32 TargetId, UAttire* AddingAttire);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSlateBrush Display_Image;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Display_Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Display_Introduction;

	UPROPERTY(meta = (BindWidget))
	class UImage* DisplayImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayIntroduction;

	static TArray<int32> AttireIds;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* AttireContainer;
};
