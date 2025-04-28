// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguelikeMapManager.h"

// Sets default values
ARoguelikeMapManager::ARoguelikeMapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARoguelikeMapManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoguelikeMapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 生成游戏地图
void ARoguelikeMapManager::GenerateMap(int32 Stages, int32 NodesPerStage)
{
    
}

// 随机选择节点类型
ERoguelikeNodeTypes ARoguelikeMapManager::GetRandomNodeType()
{
	// 随机生成战斗、宝藏、商店或事件节点
	int32 TypeIndex = FMath::RandRange(2, 4); 
	return static_cast<ERoguelikeNodeTypes>(TypeIndex);
}

// 根据坐标获取合适的世界坐标
FVector ARoguelikeMapManager::GetWorldLocationFromCoordinate(FIntVector Coordinate) const
{
	// 简单地直接转换坐标
	return FVector(Coordinate.X, Coordinate.Y, Coordinate.Z);
}

// 生成单个节点
AMapNode* ARoguelikeMapManager::SpawnNode(ERoguelikeNodeTypes NodeType, FVector Location)
{
	if (NodeTemplates.Contains(NodeType))
	{
		TSubclassOf<AMapNode> NodeClass = NodeTemplates[NodeType];
		if (NodeClass)
		{
			FActorSpawnParameters SpawnParams;
			AMapNode* NewNode = GetWorld()->SpawnActor<AMapNode>(NodeClass, Location, FRotator::ZeroRotator, SpawnParams);
			if (NewNode)
			{
				NewNode->GridCoordinate = FIntVector(Location.X / 100.0f, Location.Y / 100.0f, 0);
				AllNodes.Add(NewNode);
				return NewNode;
			}
		}
	}
	return nullptr;
}
// 连接两个节点
void ARoguelikeMapManager::ConnectNodes(AMapNode* FromNode, AMapNode* ToNode)
{
	if (FromNode && ToNode)
	{
		FNodeConnections& Connections = NodeConnections.FindOrAdd(FromNode);
		Connections.ConnectedNodes.Add(ToNode);
	}
}

