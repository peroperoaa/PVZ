// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatNode.h"

ACombatNode::ACombatNode()
	: Super()
{
	NodeType = ERoguelikeNodeTypes::Combat;

	
}


void ACombatNode::EnterNode_Implementation(APlayerController* PlayerController)
{
	Super::EnterNode_Implementation(PlayerController);
	
	// 这里可以添加进入战斗节点的逻辑
	// 例如，开始战斗、显示战斗UI等
}
