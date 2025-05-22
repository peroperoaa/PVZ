// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopNode.h"

AShopNode::AShopNode()
	: Super()
{
	// 设置节点类型为商店节点
	NodeType = ERoguelikeNodeTypes::Shop;
	
}

void AShopNode::EnterNode_Implementation(APlayerController* PlayerController)
{
	Super::EnterNode_Implementation(PlayerController);
	
}