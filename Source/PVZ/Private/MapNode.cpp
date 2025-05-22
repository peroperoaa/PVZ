// Fill out your copyright notice in the Description page of Project Settings.


#include "MapNode.h"
#include "NodeUIWidget.h"
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

void AMapNode::EnterNode_Implementation(APlayerController* PlayerController)
{
	// 标记节点已访问
	bIsVisited = true;

	
}

// 在MapNode.cpp中添加以下实现
//禁用节点的代码
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
}

