#include "RoguelikeMapManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ARoguelikeMapManager::ARoguelikeMapManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ARoguelikeMapManager::BeginPlay()
{
    Super::BeginPlay();
}

void ARoguelikeMapManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


// 生成完整地图
void ARoguelikeMapManager::GenerateMap()
{
    // 清除任何现有节点
    for (AMapNode* Node : AllNodes)
    {
        if (Node)
        {
            Node->Destroy();
        }
    }
    AllNodes.Empty();
    NodeConnections.Empty();
    MapLayers.Empty();

    // 初始化地图层级
    MapLayers.SetNum(4);

    // 设置每层的列数
    MapLayers[0].NumColumns = 3; // 第一层：3列
    MapLayers[1].NumColumns = 4; // 第二层：4列
    MapLayers[2].NumColumns = 5; // 第三层：5列
    MapLayers[3].NumColumns = 6; // 第四层：6列

    // 生成每一层的地图
    for (int32 i = 0; i < MapLayers.Num(); i++)
    {
        GenerateLayer(i);
    }

    // 连接层内的节点
    for (int32 i = 0; i < MapLayers.Num(); i++)
    {
        ConnectLayerNodes(i);
    }

    // 设置起始节点为当前节点
    if (MapLayers.Num() > 0 && MapLayers[0].Columns.Num() > 0 && MapLayers[0].Columns[0].Nodes.Num() > 0)
    {
        SetCurrentNode(MapLayers[0].Columns[0].Nodes[0]);
    }
}

// 生成特定层的地图
void ARoguelikeMapManager::GenerateLayer(int32 LayerIndex)
{
    FMapLayer& Layer = MapLayers[LayerIndex];
    Layer.Columns.SetNum(Layer.NumColumns);

    // 确定每列的行数
    TArray<int32> RowsPerColumn;

    if (LayerIndex == 0) // 第一层
    {
        // 第一列和第三列都是1行，第二列是2行
        RowsPerColumn = { 1, 2, 1 };
    }
    else if (LayerIndex == 1) // 第二层
    {
        // 每列2-3行随机
        for (int32 col = 0; col < Layer.NumColumns; col++)
        {
            RowsPerColumn.Add(FMath::RandRange(2, 3));
        }
    }
    else if (LayerIndex == 2) // 第三层 - 修改为2-3行每列
    {
        // 每列2-3行随机
        for (int32 col = 0; col < Layer.NumColumns; col++)
        {
            RowsPerColumn.Add(FMath::RandRange(2, 3));
        }
    }
    else // 第四层
    {
        // 前五列2-3行随机，最后一列只有1行(Boss)
        for (int32 col = 0; col < Layer.NumColumns - 1; col++)
        {
            RowsPerColumn.Add(FMath::RandRange(2, 3));
        }
        RowsPerColumn.Add(1); // 最后一列只有1行
    }

    // 生成各列的节点
    for (int32 col = 0; col < Layer.NumColumns; col++)
    {
        int32 numRows = RowsPerColumn[col];

        for (int32 row = 0; row < numRows; row++)
        {
            // 计算节点位置
            FVector NodeLocation(
                col * HorizontalSpacing,
                row * VerticalSpacing - (numRows - 1) * VerticalSpacing / 2.0f,
                LayerIndex * 500.0f // 不同层在不同高度
            );

            // 确定节点类型
            ERoguelikeNodeTypes NodeType = GetRandomNodeType(LayerIndex, col, row);

            // 生成节点
            AMapNode* NewNode = SpawnNode(NodeType, NodeLocation);
            if (NewNode)
            {
                // 记录节点所属的列
                Layer.Columns[col].Nodes.Add(NewNode);
            }
        }
    }
}

// 随机选择节点类型（根据层和列的约束）
ERoguelikeNodeTypes ARoguelikeMapManager::GetRandomNodeType(int32 Layer, int32 Column, int32 Row)
{
    // 根据层和位置确定节点类型
    if (Layer == 0) // 第一层
    {
        if (Column == 0) // 第一个节点
        {
            return ERoguelikeNodeTypes::Battle;
        }
        else if (Column == MapLayers[Layer].NumColumns - 1) // 最后一个节点
        {
            return ERoguelikeNodeTypes::Shop;
        }
        else // 中间节点
        {
            // 随机选择Occurrence或Battle
            return (FMath::RandBool()) ? ERoguelikeNodeTypes::Occurrence : ERoguelikeNodeTypes::Battle;
        }
    }
    else if (Layer == 1) // 第二层
    {
        if (Column == 0) // 第一个节点
        {
            return (FMath::RandBool()) ? ERoguelikeNodeTypes::Occurrence : ERoguelikeNodeTypes::Battle;
        }
        else if (Column == MapLayers[Layer].NumColumns - 1) // 最后一列
        {
            return ERoguelikeNodeTypes::Treasure;
        }
        else // 中间列不能是Treasure
        {
            TArray<ERoguelikeNodeTypes> PossibleTypes = {
                ERoguelikeNodeTypes::Battle,
                ERoguelikeNodeTypes::Occurrence,
                ERoguelikeNodeTypes::Shop
            };
            return PossibleTypes[FMath::RandRange(0, PossibleTypes.Num() - 1)];
        }
    }
    else if (Layer == 3 && Column == MapLayers[Layer].NumColumns - 1) // 最终层的最终节点
    {
        return ERoguelikeNodeTypes::Boss;
    }
    else if (Layer == 3 && Column == MapLayers[Layer].NumColumns - 2) // 最终层的倒数第二列
    {
        // 可以放一些准备性质的节点，如Shop
        return ERoguelikeNodeTypes::Shop;
    }
    else // 其他节点
    {
        // 定义可能的节点类型及其权重
        TArray<ERoguelikeNodeTypes> PossibleTypes = {
            ERoguelikeNodeTypes::Battle,
            ERoguelikeNodeTypes::Occurrence,
            ERoguelikeNodeTypes::Shop,
            ERoguelikeNodeTypes::Treasure
        };

        TArray<float> Weights = { 0.5f, 0.3f, 0.1f, 0.1f }; // 权重可以根据需要调整

        // 根据权重随机选择类型
        float TotalWeight = 0.0f;
        for (float Weight : Weights)
        {
            TotalWeight += Weight;
        }

        float Random = FMath::RandRange(0.0f, TotalWeight);
        float AccumWeight = 0.0f;

        for (int32 i = 0; i < PossibleTypes.Num(); i++)
        {
            AccumWeight += Weights[i];
            if (Random <= AccumWeight)
            {
                return PossibleTypes[i];
            }
        }

        // 默认返回战斗节点
        return ERoguelikeNodeTypes::Battle;
    }
}

// 连接层内的节点（连接每一列到下一列）
void ARoguelikeMapManager::ConnectLayerNodes(int32 LayerIndex)
{
    FMapLayer& Layer = MapLayers[LayerIndex];

    // 先连接层内的节点（连接每一列到下一列）
    for (int32 col = 0; col < Layer.NumColumns - 1; col++)
    {
        for (int32 row = 0; row < Layer.Columns[col].Nodes.Num(); row++)
        {
            AMapNode* FromNode = Layer.Columns[col].Nodes[row];

            // 确定要连接到下一列的哪些节点
            TArray<int32> TargetRows;
            int32 NextColRows = Layer.Columns[col + 1].Nodes.Num();

            // 如果下一列只有一个节点，直接连接
            if (NextColRows == 1)
            {
                TargetRows.Add(0);
            }
            else
            {
                // 确保每个节点至少连接到下一列的一个节点
                int32 NumConnections = FMath::RandRange(1, FMath::Min(2, NextColRows));

                // 随机选择要连接的行
                for (int32 i = 0; i < NumConnections; i++)
                {
                    int32 TargetRow;
                    do
                    {
                        TargetRow = FMath::RandRange(0, NextColRows - 1);
                    } while (TargetRows.Contains(TargetRow));

                    TargetRows.Add(TargetRow);
                }
            }

            // 建立连接
            for (int32 targetRow : TargetRows)
            {
                if (targetRow < Layer.Columns[col + 1].Nodes.Num())
                {
                    AMapNode* ToNode = Layer.Columns[col + 1].Nodes[targetRow];
                    ConnectNodes(FromNode, ToNode);
                }
            }
        }
    }

    // 如果不是最后一层，将本层的最后一列节点连接到下一层的第一列节点
    if (LayerIndex < MapLayers.Num() - 1)
    {
        FMapLayer& NextLayer = MapLayers[LayerIndex + 1];

        // 本层最后一列的所有节点
        for (AMapNode* FromNode : Layer.Columns[Layer.NumColumns - 1].Nodes)
        {
            // 连接到下一层的第一个节点
            if (NextLayer.Columns.Num() > 0 && NextLayer.Columns[0].Nodes.Num() > 0)
            {
                ConnectNodes(FromNode, NextLayer.Columns[0].Nodes[0]);
            }
        }
    }
}

// 获取下一个可用节点
TArray<AMapNode*> ARoguelikeMapManager::GetAvailableNextNodes(AMapNode* Node)
{
    TArray<AMapNode*> AvailableNodes;

    if (NodeConnections.Contains(Node))
    {
        return NodeConnections[Node].ConnectedNodes;
    }

    return AvailableNodes;
}

// 生成节点
AMapNode* ARoguelikeMapManager::SpawnNode(ERoguelikeNodeTypes NodeType, FVector Location)
{
    TSubclassOf<AMapNode> NodeClass = NodeTemplates.FindRef(NodeType);
    if (!NodeClass)
    {
        NodeClass = AMapNode::StaticClass();
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AMapNode* NewNode = GetWorld()->SpawnActor<AMapNode>(NodeClass, Location, FRotator::ZeroRotator, SpawnParams);
    if (NewNode)
    {
        NewNode->GridCoordinate = FIntVector(Location.X / 100.0f, Location.Y / 100.0f, Location.Z / 100.0f);
        NewNode->NodeType = NodeType;
        AllNodes.Add(NewNode);
    }
    
    return NewNode;
}

// 连接节点
void ARoguelikeMapManager::ConnectNodes(AMapNode* FromNode, AMapNode* ToNode)
{
    if (FromNode && ToNode)
    {
        FNodeConnections& Connections = NodeConnections.FindOrAdd(FromNode);
        Connections.ConnectedNodes.AddUnique(ToNode);
    }
}

// 处理节点激活事件
void ARoguelikeMapManager::HandleNodeActivated(AMapNode* ActivatedNode)
{
    // 处理节点激活事件
    CurrentNode = ActivatedNode;
    
    // 如果需要，可以在这里触发委托
    if (OnNodeActivated.IsBound())
    {
        OnNodeActivated.Broadcast(ActivatedNode);
    }
}

// 设置当前节点
void ARoguelikeMapManager::SetCurrentNode(AMapNode* Node)
{
    if (Node)
    {
        CurrentNode = Node;
        HandleNodeActivated(Node);
    }
}

// 激活节点
bool ARoguelikeMapManager::ActivateNode(AMapNode* NodeToActivate)
{
    // 检查节点是否可达
    if (CurrentNode && NodeConnections.Contains(CurrentNode))
    {
        if (NodeConnections[CurrentNode].ConnectedNodes.Contains(NodeToActivate))
        {
            NodeToActivate->bIsVisited = true;
            SetCurrentNode(NodeToActivate);
            
            // 调用节点的进入函数
            if (UGameplayStatics::GetPlayerController(this, 0))
            {
                NodeToActivate->EnterNode(UGameplayStatics::GetPlayerController(this, 0));
            }
            
            return true;
        }
    }
    
    return false;
}

// 获取当前节点
FVector ARoguelikeMapManager::GetWorldLocationFromCoordinate(FIntVector Coordinate) const
{
    return FVector(Coordinate.X, Coordinate.Y, Coordinate.Z);
}
