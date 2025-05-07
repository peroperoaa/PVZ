#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapNode.h"
#include "RoguelikeMapManager.generated.h"

// 存储节点连接关系的结构体
USTRUCT(BlueprintType)
struct FNodeConnections
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<AMapNode*> ConnectedNodes;
};

// 表示一列节点的结构体
USTRUCT(BlueprintType)
struct FMapColumn
{
    GENERATED_BODY()
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<AMapNode*> Nodes;
};

// 存储层级信息的结构体
USTRUCT(BlueprintType)
struct FMapLayer
{
    GENERATED_BODY()

    // 该层的所有节点，按列组织
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<FMapColumn> Columns;
    
    // 该层的列数
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 NumColumns;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNodeActivatedSignature, AMapNode*, ActivatedNode);

UCLASS()
class PVZ_API ARoguelikeMapManager : public AActor
{
    GENERATED_BODY()

public:
    ARoguelikeMapManager();

protected:
    virtual void BeginPlay() override;

    // 处理节点激活事件
    void HandleNodeActivated(AMapNode* ActivatedNode);

    // 随机选择节点类型（根据层和列的约束）
    UFUNCTION(BlueprintCallable, Category = "Roguelike")
    ERoguelikeNodeTypes GetRandomNodeType(int32 Layer, int32 Column, int32 Row);

    // 根据坐标获取世界位置
    FVector GetWorldLocationFromCoordinate(FIntVector Coordinate) const;

    // 存储所有生成的节点
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roguelike")
    TArray<AMapNode*> AllNodes;

    // 当前活动的节点
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roguelike")
    AMapNode* CurrentNode;

    // 节点间的连接关系
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roguelike")
    TMap<AMapNode*, FNodeConnections> NodeConnections;

    // 节点类型到节点类的映射
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roguelike")
    TMap<ERoguelikeNodeTypes, TSubclassOf<AMapNode>> NodeTemplates;

    // 地图层级信息
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roguelike")
    TArray<FMapLayer> MapLayers;

    // 节点间的水平和垂直间距
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roguelike")
    float HorizontalSpacing = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roguelike")
    float VerticalSpacing = 300.0f;

    // 生成特定层的地图
    void GenerateLayer(int32 LayerIndex);

    // 为层间节点建立连接
    void ConnectLayerNodes(int32 LayerIndex);

public:
    virtual void Tick(float DeltaTime) override;

    // 生成完整地图
    UFUNCTION(BlueprintCallable, Category = "Roguelike")
    void GenerateMap();

    // 节点管理方法
    UFUNCTION(BlueprintCallable, Category = "Roguelike")
    AMapNode* SpawnNode(ERoguelikeNodeTypes NodeType, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Roguelike")
    void ConnectNodes(AMapNode* FromNode, AMapNode* ToNode);

    // 获取下一个可用节点
    UFUNCTION(BlueprintCallable, Category = "Roguelike")
    TArray<AMapNode*> GetAvailableNextNodes(AMapNode* Node);

    // 切换节点方法
    UFUNCTION(BlueprintCallable, Category = "Roguelike")
    bool ActivateNode(AMapNode* NodeToActivate);

    // 获取当前节点
    UFUNCTION(BlueprintPure, Category = "Roguelike")
    AMapNode* GetCurrentNode() const { return CurrentNode; }

    // 设置当前节点
    UFUNCTION(BlueprintCallable, Category = "Roguelike")
    void SetCurrentNode(AMapNode* Node);

    // 节点激活事件委托
    UPROPERTY(BlueprintAssignable, Category = "Roguelike")
    FNodeActivatedSignature OnNodeActivated;
};