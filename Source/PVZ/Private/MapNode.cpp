// Fill out your copyright notice in the Description page of Project Settings.


#include "MapNode.h"
#include "NodeUIWidget.h"
#include "RoguelikeCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMapNode::AMapNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 设置此Actor每帧调用Tick()
	PrimaryActorTick.bCanEverTick = true;

	// 初始化可视化组件
	NodeVisualComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NodeVisualComponent"));
	RootComponent = NodeVisualComponent;

	// 初始化Widget组件
	NodeWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NodeWidgetComponent"));

	NodeWidgetComponent->SetupAttachment(NodeVisualComponent);

	// 设置Widget组件的属性
	static ConstructorHelpers::FClassFinder<UUserWidget> NodeWidgetClassFinder(TEXT("/Game/Blueprint/UI_Node/WBP_NodeUI"));
	if (NodeWidgetClassFinder.Succeeded())
	{
		NodeWidgetComponent->SetWidgetClass(NodeWidgetClassFinder.Class);
	}
	NodeWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen); // 设置为屏幕空间
	NodeWidgetComponent->SetDrawSize(FVector2D(200, 100)); // 设置Widget大小

	
	// 如果需要静态网格，可以改用UStaticMeshComponent
	// UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	// MeshComponent->SetupAttachment(NodeVisualComponent);

}

// Called when the game starts or when spawned
void AMapNode::BeginPlay()
{
	Super::BeginPlay();
    
	// 获取创建的Widget并设置节点
	if (NodeWidgetComponent)
	{
		// 必须延迟一帧等待widget创建完成
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimerForNextTick([this]()
		{
			UNodeUIWidget* NodeUI = Cast<UNodeUIWidget>(NodeWidgetComponent->GetUserWidgetObject());
			if (NodeUI)
			{
				NodeUI->SetNode(this);
			}
		});
	}
}

// Called every frame
void AMapNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 进入节点的实现
 void AMapNode::EnterNode_Implementation(APlayerController* PlayerController)
 {
	// 设置进入的节点为已访问
 	VisitNode(this);
     
 	// 获取地图管理器
 	ARoguelikeMapManager* MapManager = nullptr;
 	TArray<AActor*> FoundActors;
 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoguelikeMapManager::StaticClass(), FoundActors);
 	if (FoundActors.Num() > 0)
 	{
 		MapManager = Cast<ARoguelikeMapManager>(FoundActors[0]);
 	}
     
 	if (!MapManager)
 		return;

	// 1.将同一列的节点设置为不可访问
	TArray<AMapNode*> NodesInSameColumn;
	MapManager->GetNodesInSameColumn(this, NodesInSameColumn);
	for (AMapNode* Node : NodesInSameColumn)
	{
		Node->bIsEnterable = false;
	}
	
	// 2. 激活与当前节点直接相连的节点
	for (AMapNode* ConnectedNode : ConnectedNodes)
	{
		if (!ConnectedNode->bIsVisited)
		{
			ConnectedNode->SetEnterable(ConnectedNode);
		}
	}
	
	// 3. 禁用当前层中所有不可达节点
	// 3.1.获取当前层的所有可达节点
	TArray<AMapNode*> AccessibleNodes;
	CollectAccessibleNodesInLayer(MapManager, AccessibleNodes);

	// 3.2禁用当前层中所有不可达节点
	DisableInaccessibleNodesInLayer(MapManager, AccessibleNodes);
	
 	// 更新连接的可视状态
 	MapManager->UpdateConnectionVisuals(this);

	
	ARoguelikeCharacter* Character = Cast<ARoguelikeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Character && bIsLastNodeInLayer)
	{
		Character->MoveToLayer(LayerIndex + 1, 1.0f);
	}
	
 	//进入节点具体内容..
	
 }

// 禁用节点
void AMapNode::DisableNode(AMapNode* NodeToDisable)
{
	if (!NodeToDisable)
		return;

	// 设置节点为禁用状态
	NodeToDisable->bIsDisabled = true;

	// 更新节点UI以显示禁用状态
	UNodeUIWidget* NodeUI = Cast<UNodeUIWidget>(NodeToDisable->NodeWidgetComponent->GetUserWidgetObject());
	if (NodeUI)
	{
		NodeUI->UpdateNodeState();
	}
	
	// 禁用节点的交互性
	NodeToDisable->SetActorEnableCollision(false);

	// 获取地图管理器
	ARoguelikeMapManager* MapManager = nullptr;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(NodeToDisable->GetWorld(), ARoguelikeMapManager::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		MapManager = Cast<ARoguelikeMapManager>(FoundActors[0]);
		if (MapManager)
		{
			// 隐藏与该节点相关的所有连接线
			MapManager->HideConnectionsForNode(NodeToDisable);
		}
	}
}

// 设置已访问节点
void AMapNode::VisitNode(AMapNode* NodeToVisit)
{
	if (!NodeToVisit)
		return;

	// 标记节点已访问
	NodeToVisit->bIsVisited = true;
	
	UNodeUIWidget* NodeUI = Cast<UNodeUIWidget>(NodeToVisit->NodeWidgetComponent->GetUserWidgetObject());
	if (NodeUI)
	{
		NodeUI->UpdateNodeState();
	}
	
	NodeToVisit->SetActorEnableCollision(false);
}

// 设置节点为可访问
void AMapNode::SetEnterable(AMapNode* NodeToSet)
{
	if (!NodeToSet)
		return;
	
	NodeToSet->bIsEnterable = true;

	UNodeUIWidget* NodeUI = Cast<UNodeUIWidget>(NodeToSet->NodeWidgetComponent->GetUserWidgetObject());
	if (NodeUI)
	{
		NodeUI->UpdateNodeState();
	}
	
}

// 使用BFS收集此层当前可达的所有节点
void AMapNode::CollectAccessibleNodesInLayer(ARoguelikeMapManager* MapManager, TArray<AMapNode*>& AccessibleNodes)
{
	AccessibleNodes.Empty();
	TSet<AMapNode*> Visited;

	// 收集当前层的所有当前可访问节点作为BFS起点
	TArray<AMapNode*> Queue;
    
	if (LayerIndex >= 0 && LayerIndex < MapManager->MapLayers.Num())
	{
		const FMapLayer& CurrentLayer = MapManager->MapLayers[LayerIndex];
		for (const FMapColumn& Column : CurrentLayer.Columns)
		{
			for (AMapNode* Node : Column.Nodes)
			{
				if (Node->bIsEnterable)
				{
					Queue.Add(Node);
					Visited.Add(Node);
					AccessibleNodes.AddUnique(Node);
				}
			}
		}
	}

	// BFS寻找所有可达节点
	int32 Index = 0;
	while (Index < Queue.Num())
	{
		AMapNode* CurrentNode = Queue[Index++];
        
		for (AMapNode* ConnectedNode : CurrentNode->ConnectedNodes)
		{
			// 确保节点在同一层且未处理过
			if (ConnectedNode->LayerIndex == LayerIndex && !Visited.Contains(ConnectedNode))
			{
				Visited.Add(ConnectedNode);
                
				// 只有未被禁用的节点才是可达的
				if (!ConnectedNode->bIsDisabled)
				{
					AccessibleNodes.AddUnique(ConnectedNode);
					Queue.Add(ConnectedNode);
				}
			}
		}
	}
}

// 禁用当前层所有不可访问的节点
void AMapNode::DisableInaccessibleNodesInLayer(ARoguelikeMapManager* MapManager, const TArray<AMapNode*>& AccessibleNodes)
{
	// 获取当前层的所有节点
	if (LayerIndex >= 0 && LayerIndex < MapManager->MapLayers.Num())
	{
		const FMapLayer& CurrentLayer = MapManager->MapLayers[LayerIndex];
		for (const FMapColumn& Column : CurrentLayer.Columns)
		{
			for (AMapNode* Node : Column.Nodes)
			{
				// 如果节点未被访问、未被禁用且不在可访问节点集合中
				if (!Node->bIsVisited && !Node->bIsDisabled && !AccessibleNodes.Contains(Node))
				{
					DisableNode(Node);
				}
			}
		}
	}
}


