// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleNode.h"

void ABattleNode::EnterNode_Implementation(APlayerController* PlayerController)
{
	// 先调用父类实现
	Super::EnterNode_Implementation(PlayerController);
    
	// 战斗节点特有的逻辑
	
	OnNodeActivated.Broadcast(this);
    
	// 这里添加战斗节点特有的行为
	UE_LOG(LogTemp, Log, TEXT("进入战斗节点：%s"), *GetName());
    
	// 战斗相关逻辑...
}