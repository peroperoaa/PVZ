// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TeamSelectInterface.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API UTeamSelectInterface : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	FString Team;

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Team1;

	UPROPERTY(meta = (BindWidget))
	class UButton* Team2;

	UPROPERTY(meta = (BindWidget))
	class UButton* Team3;

	UPROPERTY(meta = (BindWidget))
	class UButton* Team4;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SelectedTeam;

	UFUNCTION()
	void Team1ButtonClicked();

	UFUNCTION()
	void Team2ButtonClicked();

	UFUNCTION()
	void Team3ButtonClicked();

	UFUNCTION()
	void Team4ButtonClicked();
};
