// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguelikeGameInstance.h"

void URoguelikeGameInstance::Init()
{
	Super::Init();
    
	// 使用蓝图类而不是C++类
	UClass* StateManagerClass = LoadClass<URoguelikeStateManager>(
		nullptr, 
		TEXT("/Game/Blueprint/BP_RoguelikeStateManager.BP_RoguelikeStateManager_C")
	);
    
	if (!StateManagerClass)
	{
		// 如果找不到蓝图，回退到C++类
		StateManagerClass = URoguelikeStateManager::StaticClass();
		UE_LOG(LogTemp, Warning, TEXT("未找到StateManager蓝图，使用默认C++类"));
	}
    
	StateManager = NewObject<URoguelikeStateManager>(this, StateManagerClass);
    
	if (StateManager)
	{
		StateManager->InitializeDefaultValues();
	}
	
}