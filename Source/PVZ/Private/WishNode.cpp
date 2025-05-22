// Fill out your copyright notice in the Description page of Project Settings.


#include "WishNode.h"

AWishNode::AWishNode()
	: Super()
{
	// 设置节点类型为愿望节点
	NodeType = ERoguelikeNodeTypes::Wish;
	
	// 这里可以添加其他初始化逻辑
}

void AWishNode::EnterNode_Implementation(APlayerController* PlayerController)
{
	Super::EnterNode_Implementation(PlayerController);
	
	// 这里可以添加进入愿望节点的逻辑
	// 例如，显示愿望UI、处理愿望选择等
}