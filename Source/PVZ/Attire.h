// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateBrush.h"
#include "Engine/DataTable.h"
#include "Attire.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAttireInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateBrush AttireImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AttireName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttireId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AttireIntroduction;
};


UCLASS()
class PVZ_API UAttire : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAttireInfo AttireInfo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UDataTable* AttireInfoTable;

	UFUNCTION(BlueprintCallable)
	const FAttireInfo& GetAttireInfoByAttireId(int32 InAttireId) const;

protected:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UFUNCTION()
	void ButtonClicked();
};
