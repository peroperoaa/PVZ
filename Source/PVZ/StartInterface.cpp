// Fill out your copyright notice in the Description page of Project Settings.


#include "StartInterface.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

UUserWidget* CurrentWidget = nullptr; // 保存当前控件的引用

bool UStartInterface::Initialize()
{
	// 如果父类初始化失败，则返回false
	if (!Super::Initialize()) {
		return false;
	}
	return true;
}

