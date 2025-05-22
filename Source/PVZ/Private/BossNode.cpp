// Fill out your copyright notice in the Description page of Project Settings.


#include "BossNode.h"

ABossNode::ABossNode()
	: Super()
{
	// 设置节点类型为Boss节点
	NodeType = ERoguelikeNodeTypes::Boss;
	
	// 这里可以添加其他初始化逻辑
}

void ABossNode::EnterNode_Implementation(APlayerController* PlayerController)
{
	Super::EnterNode_Implementation(PlayerController);
	
}
