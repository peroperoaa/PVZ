// Fill out your copyright notice in the Description page of Project Settings.


#include "MapNode.h"

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
	
}

// Called every frame
void AMapNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapNode::EnterNode_Implementation(APlayerController* PlayerController)
{
	// Implement the logic for entering the node here
	bIsVisited = true;
	
}

// 在MapNode.cpp中添加以下实现
//禁用节点的代码


