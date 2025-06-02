// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CollectionCard.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API UCollectionCard : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UFUNCTION()
	void ButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UAttire* UI_Attire;
	
};
