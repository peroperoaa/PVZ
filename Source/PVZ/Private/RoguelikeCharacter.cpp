// RoguelikeCharacter.cpp
#include "RoguelikeCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ARoguelikeCharacter::ARoguelikeCharacter()
{
	// 设置不使用控制器旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 创建摄像机组件
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(RootComponent);
	TopDownCamera->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	TopDownCamera->bUsePawnControlRotation = false;
}

void ARoguelikeCharacter::BeginPlay()
{
	Super::BeginPlay();
    
	// 初始化摄像机位置
	SetActorLocation(FVector(0.0f, FixedCameraY, CameraHeight));
	
}

void ARoguelikeCharacter::SetCameraPositionX(float XPosition)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.X = XPosition;
	SetActorLocation(NewLocation);
}

void ARoguelikeCharacter::MoveCamera(float XDelta)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.X += XDelta;
	SetActorLocation(NewLocation);
}

// 获取摄像机当前位置
FVector ARoguelikeCharacter::GetCameraLocation() const
{
	if (TopDownCamera)
	{
		return TopDownCamera->GetComponentLocation();
	}
	return GetActorLocation(); // 摄像机不存在时返回角色位置
}

// 设置摄像机位置
void ARoguelikeCharacter::SetCameraLocation(const FVector& NewLocation)
{
	if (TopDownCamera)
	{
		// 设置新位置，但保持Y轴固定
		TopDownCamera->SetWorldLocation(FVector(NewLocation.X, FixedCameraY, NewLocation.Z));
	}
}