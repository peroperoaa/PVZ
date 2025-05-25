#include "RoguelikeMapManager.h"
#include "Engine/World.h"
#include "RoguelikeCharacter.h"
#include "Kismet/GameplayStatics.h"

ARoguelikeMapManager::ARoguelikeMapManager()
{
    PrimaryActorTick.bCanEverTick = true;
    MapNames = { "/Game/Map/NodeMap/Region1", "/Game/Map/NodeMap/Region2", "/Game/Map/NodeMap/Region3", "/Game/Map/NodeMap/Region4" };
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

    // 设置每层第一列节点为可访问
    for (int32 i = 0; i < MapLayers.Num(); i++)
    {
        if (MapLayers[i].Columns.Num() > 0)
        {
            for (AMapNode* Node : MapLayers[i].Columns[0].Nodes)
            {
                Node->bIsEnterable = true;
            }
        }
    }
    
    // 设置起始节点为当前节点
    if (MapLayers.Num() > 0 && MapLayers[0].Columns.Num() > 0 && MapLayers[0].Columns[0].Nodes.Num() > 0)
    {
        SetCurrentNode(MapLayers[0].Columns[0].Nodes[0]);
    }

    // 标记每层最后一列的节点
    for (int32 i = 0; i < MapLayers.Num(); i++)
    {
        FMapLayer& Layer = MapLayers[i];
        if (Layer.Columns.Num() > 0)
        {
            // 获取最后一列
            FMapColumn& LastColumn = Layer.Columns.Last();
            for (AMapNode* Node : LastColumn.Nodes)
            {
                if (Node)
                {
                    Node->bIsLastNodeInLayer = true;
                }
            }
        }
    }

    //获取玩家摄像机
    ARoguelikeCharacter* Character = Cast<ARoguelikeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (Character)
    {
        Character->MapManager = this;
        Character->SetupLayerBounds(MapLayers);
        
        // 初始设置为第一层
        Character->MoveToLayer(0, 0.0f); // 无过渡动画
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
            if (col == 0)
            {
                RowsPerColumn.Add(2); // 第一列固定为2行
            }
            else
            {
                RowsPerColumn.Add(FMath::RandRange(2, 3));
            }
        }
    }
    else if (LayerIndex == 2) // 第三层
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
                (LayerIndex * LayerHorizontalOffset) + (col * HorizontalSpacing),
                row * VerticalSpacing - (numRows - 1) * VerticalSpacing / 2.0f,
                0.0f
            );

            // 确定节点类型
            ERoguelikeNodeTypes NodeType = GetRandomNodeType(LayerIndex, col, row);

            // 生成节点
            AMapNode* NewNode = SpawnNode(NodeType, NodeLocation);
            if (NewNode)
            {
                // 记录节点所属的列
                NewNode->ColumnIndex = col; // 设置列号
                NewNode->LayerIndex = LayerIndex; // 设置层号
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
            return ERoguelikeNodeTypes::Combat;
        }
        else if (Column == MapLayers[Layer].NumColumns - 1) // 最后一个节点
        {
            return ERoguelikeNodeTypes::Shop;
        }
        else // 中间节点
        {
            // 随机选择Encounter或Combat
            return (FMath::RandBool()) ? ERoguelikeNodeTypes::Encounter : ERoguelikeNodeTypes::Combat;
        }
    }
    else if (Layer == 1) // 第二层
    {
        if (Column == 0) // 第一列节点
        {
            return (FMath::RandBool()) ? ERoguelikeNodeTypes::Encounter : ERoguelikeNodeTypes::Combat;
        }
        else if (Column == MapLayers[Layer].NumColumns - 1) // 最后一列
        {
            return ERoguelikeNodeTypes::Wish;
        }
        else // 中间列不能是Wish
        {
            TArray<ERoguelikeNodeTypes> PossibleTypes = {
                ERoguelikeNodeTypes::Combat,
                ERoguelikeNodeTypes::Encounter,
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
            ERoguelikeNodeTypes::Combat,
            ERoguelikeNodeTypes::Encounter,
            ERoguelikeNodeTypes::Shop,
            ERoguelikeNodeTypes::Wish
        };

        TArray<float> Weights = { 0.55f, 0.3f, 0.08f, 0.07f }; // 权重可以根据需要调整

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
        return ERoguelikeNodeTypes::Combat;
    }
}

// 连接层内的节点（连接每一列到下一列）
void ARoguelikeMapManager::ConnectLayerNodes(int32 LayerIndex)
{
    FMapLayer& Layer = MapLayers[LayerIndex];

    // 仅连接层内的节点（从每一列连接到下一列）
    for (int32 col = 0; col < Layer.NumColumns - 1; col++)
    {
        TArray<AMapNode*>& CurrentColNodes = Layer.Columns[col].Nodes;
        TArray<AMapNode*>& NextColNodes = Layer.Columns[col + 1].Nodes;

        // 第一步：每个节点优先连接到下一列符合方向偏好的最近节点
        for (AMapNode* FromNode : CurrentColNodes)
        {
            // 获取源节点的Y坐标
            float FromNodeY = FromNode->GetActorLocation().Y;
            
            // 初始化优先方向和备选节点
            AMapNode* PreferredNode = nullptr;
            AMapNode* FallbackNode = nullptr;
            float PreferredDistance = MAX_FLT;
            float FallbackDistance = MAX_FLT;

            // 遍历下一列所有节点
            for (AMapNode* ToNode : NextColNodes)
            {
                float ToNodeY = ToNode->GetActorLocation().Y;
                float Distance = FMath::Abs(FromNodeY - ToNodeY);
                
                // 根据源节点位置的正负，判断是否为优先方向
                bool IsPreferred = (FromNodeY > 0 && ToNodeY > FromNodeY) || 
                                   (FromNodeY < 0 && ToNodeY < FromNodeY);
                
                if (IsPreferred)
                {
                    // 更新优先方向的最近节点
                    if (Distance < PreferredDistance)
                    {
                        PreferredDistance = Distance;
                        PreferredNode = ToNode;
                    }
                }
                else
                {
                    // 更新非优先方向的备选节点
                    if (Distance < FallbackDistance)
                    {
                        FallbackDistance = Distance;
                        FallbackNode = ToNode;
                    }
                }
            }

            // 优先连接到首选节点，如果没有则连接到备选节点
            AMapNode* NodeToConnect = PreferredNode ? PreferredNode : FallbackNode;
            if (NodeToConnect)
            {
                ConnectNodes(FromNode, NodeToConnect);
            }
        }
        
        // 第二步：确保下一列每个节点至少有一个连接
        for (AMapNode* ToNode : NextColNodes)
        {
            bool HasConnection = false;
            
            // 检查是否已有连接
            for (AMapNode* FromNode : CurrentColNodes)
            {
                if (NodeConnections.Contains(FromNode) && 
                    NodeConnections[FromNode].ConnectedNodes.Contains(ToNode))
                {
                    HasConnection = true;
                    break;
                }
            }
            
            // 如果没有连接，随机连接一个
            if (!HasConnection && CurrentColNodes.Num() > 0)
            {
                int32 RandomIndex = FMath::RandRange(0, CurrentColNodes.Num() - 1);
                ConnectNodes(CurrentColNodes[RandomIndex], ToNode);
            }
        }

        // 第三步：再为前一列的节点添加额外的连接
        for (int32 row = 0; row < Layer.Columns[col].Nodes.Num(); row++)
        {
            AMapNode* FromNode = Layer.Columns[col].Nodes[row];

            // 确定要连接到下一列的哪些节点
            TArray<int32> TargetRows;
            int32 NextColRows = Layer.Columns[col + 1].Nodes.Num();

            // 随机决定连接的数量（0-2个）
            int32 NumConnections = FMath::RandRange(0, FMath::Min(2, NextColRows));

            // 随机选择要连接的行
            for (int32 i = 0; i < NumConnections; i++)
            {
                int32 TargetRow = FMath::RandRange(0, NextColRows - 1);
                TargetRows.AddUnique(TargetRow);
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
        FromNode->ConnectedNodes.AddUnique(ToNode);// 添加到当前节点的连接列表
        
        FNodeConnections& Connections = NodeConnections.FindOrAdd(FromNode);
        Connections.ConnectedNodes.AddUnique(ToNode);
        
        // 创建可视连接
        CreateVisualConnection(FromNode, ToNode);
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
    // 检查节点是否可达并可访问
    if (CurrentNode && NodeConnections.Contains(CurrentNode) &&
       NodeConnections[CurrentNode].ConnectedNodes.Contains(NodeToActivate) &&
       NodeToActivate->bIsEnterable)
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

// 实现创建可视连接的方法
ANodeConnection* ARoguelikeMapManager::CreateVisualConnection(AMapNode* FromNode, AMapNode* ToNode)
{
    if (!FromNode || !ToNode || !ConnectionClass)
        return nullptr;
    
    // 检查连接是否已存在
    FNodeVisualConnections& FromConnections = VisualConnections.FindOrAdd(FromNode);
    if (FromConnections.Connections.Contains(ToNode))
        return FromConnections.Connections[ToNode];
    
    // 创建新的连接Actor
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    ANodeConnection* Connection = GetWorld()->SpawnActor<ANodeConnection>(ConnectionClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    
    if (Connection)
    {
        // 设置连接的属性
        Connection->ConnectionMesh = ConnectionMesh;
        Connection->ConnectionMaterial = NormalConnectionMaterial;
        Connection->ActiveConnectionMaterial = ActiveConnectionMaterial;
        
        // 设置连接的起点和终点
        FVector StartPos = FromNode->GetActorLocation();
        FVector EndPos = ToNode->GetActorLocation();
        
        // 调整位置使线条不穿过节点图标
        FVector Direction = (EndPos - StartPos).GetSafeNormal();
        StartPos += Direction * 50.0f;  // 可以调整这些数值
        EndPos -= Direction * 50.0f;
        
        Connection->SetupConnection(StartPos, EndPos);
        
        // 存储连接引用
        FromConnections.Connections.Add(ToNode, Connection);
        return Connection;
    }
    
    return nullptr;
}

// 实现更新连接可视状态的方法
void ARoguelikeMapManager::UpdateConnectionVisuals(AMapNode* Node)
{
    if (!Node || !VisualConnections.Contains(Node))
        return;
        
    // 获取当前节点的所有连接
    FNodeVisualConnections& Connections = VisualConnections[Node];

    for (auto& Pair : Connections.Connections)
    {
        AMapNode* ConnectedNode = Pair.Key;
        ANodeConnection* Connection = Pair.Value;
        
        // 根据节点是否被访问设置连接的可视状态
        bool bActive = Node->bIsVisited && NodeConnections.Contains(Node) && 
                       NodeConnections[Node].ConnectedNodes.Contains(ConnectedNode);
        
        if (Connection)
        {
            Connection->SetActive(bActive);
        }
    }
}

// 获取与指定节点同一列的所有节点
void ARoguelikeMapManager::GetNodesInSameColumn(AMapNode* Node, TArray<AMapNode*>& OutNodes)
{
    OutNodes.Empty();
    if (!Node)
        return;

    int32 LayerIndex = Node->LayerIndex;
    int32 ColumnIndex = Node->ColumnIndex;
    
    // 检查LayerIndex和ColumnIndex是否有效
    if (LayerIndex >= 0 && LayerIndex < MapLayers.Num())
    {
        const FMapLayer& Layer = MapLayers[LayerIndex];
        if (ColumnIndex >= 0 && ColumnIndex < Layer.Columns.Num())
        {
            // 只获取同一层级同列的节点
            OutNodes = Layer.Columns[ColumnIndex].Nodes;
        }
    }
}


// 隐藏与指定节点相关的连接
void ARoguelikeMapManager::HideConnectionsForNode(AMapNode* Node)
{
    if (!Node)
        return;
        
    // 处理从该节点出发的所有连接
    if (VisualConnections.Contains(Node))
    {
        FNodeVisualConnections& NodeVisuals = VisualConnections[Node];
        for (auto& Pair : NodeVisuals.Connections)
        {
            ANodeConnection* Connection = Pair.Value;
            if (Connection)
            {
                Connection->SetActorHiddenInGame(true);
                Connection->SetActorEnableCollision(false);
            }
        }
    }
    
    // 处理指向该节点的所有连接
    for (auto& VisualPair : VisualConnections)
    {
        AMapNode* FromNode = VisualPair.Key;
        FNodeVisualConnections& NodeVisuals = VisualPair.Value;
        
        // 检查是否有连接到达目标节点
        if (NodeVisuals.Connections.Contains(Node))
        {
            ANodeConnection* Connection = NodeVisuals.Connections[Node];
            if (Connection)
            {
                Connection->SetActorHiddenInGame(true);
                Connection->SetActorEnableCollision(false);
            }
        }
    }
}