// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapNode.h"
#include "RoguelikeMapManager.generated.h"

USTRUCT(BlueprintType)
struct FNodeConnections
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AMapNode*> ConnectedNodes;
};

UCLASS()
class PVZ_API ARoguelikeMapManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoguelikeMapManager();
	
    
protected:
	virtual void BeginPlay() override;
	
	// 存储所有生成的节点
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roguelike")
	TArray<AMapNode*> AllNodes;

	// 节点间的连接关系
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roguelike")
	TMap<AMapNode*, FNodeConnections> NodeConnections;

	// 节点类型到节点类的映射
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roguelike")
	TMap<ERoguelikeNodeTypes, TSubclassOf<AMapNode>> NodeTemplates;

	// 随机选择节点类型
	UFUNCTION(BlueprintCallable, Category = "Roguelike")
	ERoguelikeNodeTypes GetRandomNodeType();

	// 根据坐标获取合适的世界坐标
	FVector GetWorldLocationFromCoordinate(FIntVector Coordinate) const;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 生成游戏地图
	UFUNCTION(BlueprintCallable, Category = "Roguelike")
	void GenerateMap(int32 Stages = 5, int32 NodesPerStage = 3);

	// 生成单个节点
	UFUNCTION(BlueprintCallable, Category = "Roguelike")
	AMapNode* SpawnNode(ERoguelikeNodeTypes NodeType, FVector Location);

	// 连接两个节点
	UFUNCTION(BlueprintCallable, Category = "Roguelike")
	void ConnectNodes(AMapNode* FromNode, AMapNode* ToNode);
	
	//
	
};
