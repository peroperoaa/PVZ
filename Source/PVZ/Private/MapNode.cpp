// Fill out your copyright notice in the Description page of Project Settings.


#include "MapNode.h"

// Sets default values
AMapNode::AMapNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

