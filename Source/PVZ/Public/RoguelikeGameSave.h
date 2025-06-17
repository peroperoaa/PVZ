// RoguelikeGameSave.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RoguelikeStateEnum.h"
#include "RoguelikeGameSave.generated.h"

UCLASS()
class PVZ_API URoguelikeGameSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<ERoguelikeStateEnum, float> SavedStateValues;

	UPROPERTY()
	int32 SaveSlotIndex;
};