// Fill out your copyright notice in the Description page of Project Settings.


#include "StartInterface.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UStartInterface::Initialize()
{
	// 如果父类初始化失败，则返回false
	if (!Super::Initialize()) {
		return false;
	}

	// 如果按钮存在，则绑定点击事件
	if (Button_Adventure) {
		Button_Adventure->OnClicked.AddDynamic(this, &UStartInterface::Button_AdventureClicked);
	}
	return true;
}

void UStartInterface::Button_AdventureClicked()
{
	// 设置按钮不可用
	Button_Adventure->SetIsEnabled(false);

	// 打开新关卡
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("JumpTestLevel"));
}
