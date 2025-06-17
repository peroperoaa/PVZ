#include "CombatNode.h"
#include "Kismet/GameplayStatics.h"
#include "RoguelikeGameInstance.h"

ACombatNode::ACombatNode()
	: Super()
{
	NodeType = ERoguelikeNodeTypes::Combat;
}

void ACombatNode::EnterNode_Implementation(APlayerController* PlayerController)
{
	Super::EnterNode_Implementation(PlayerController);
	
}

// 从GameInstance获取StateManager
URoguelikeStateManager* ACombatNode::GetStateManager() const
{
	// 获取GameInstance
	URoguelikeGameInstance* GameInstance = Cast<URoguelikeGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance && GameInstance->StateManager)
	{
		return GameInstance->StateManager;
	}
    
	UE_LOG(LogTemp, Warning, TEXT("无法获取StateManager"));
	return nullptr;
}

void ACombatNode::OnCombatCompleted(bool bVictory)
{
	if (bVictory)
	{
		URoguelikeStateManager* StateManager = GetStateManager();
		if (StateManager)
		{
			StateManager->ApplyBattleVictoryRewards();
			UE_LOG(LogTemp, Log, TEXT("战斗胜利，已应用奖励"));
		}
	}
	else
	{
		URoguelikeStateManager* StateManager = GetStateManager();
		if (StateManager)
		{
			StateManager->ApplyBattleDefeatPenalties();
			UE_LOG(LogTemp, Log, TEXT("战斗失败，已应用惩罚"));
		}
	}
	
	// 卸载战斗关卡
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "OnLevelUnloaded";
	LatentInfo.UUID = FGuid::NewGuid().A;
	LatentInfo.Linkage = 0;

	UGameplayStatics::UnloadStreamLevel(
		this,            // WorldContextObject
		CombatLevelName, // LevelName
		LatentInfo,      // LatentInfo
		false            // bShouldBlockOnUnload
	);
}

void ACombatNode::OnLevelUnloaded_Implementation(const FName& LevelName)
{
	
}


