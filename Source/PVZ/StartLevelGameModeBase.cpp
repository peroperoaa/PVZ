// Fill out your copyright notice in the Description page of Project Settings.


#include "StartLevelGameModeBase.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"

AStartLevelGameModeBase::AStartLevelGameModeBase()
{
	
}

void AStartLevelGameModeBase::BeginPlay() {
	Super::BeginPlay();
	// 获取PlayerController
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// 使鼠标可见并启用点击和悬停事件
	if (PlayerController) {
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}

	
}
