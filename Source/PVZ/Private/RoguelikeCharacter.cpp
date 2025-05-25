// RoguelikeCharacter.cpp
#include "RoguelikeCharacter.h"
#include "Camera/CameraComponent.h"
#include "RoguelikeMapManager.h"
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
	
	// 初始化摄像机位置和当前层索引
	CurrentLayerIndex = 0;
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

// 修改MoveToLayer方法，添加详细日志
void ARoguelikeCharacter::MoveToLayer(int32 LayerIndex, float TransitionTime)
{
	if (LayerIndex >= 0 && LayerIndex < LayerBounds.Num())
	{
		// 更新当前层索引
		CurrentLayerIndex = LayerIndex;
		
		FBox TargetBounds = LayerBounds[LayerIndex];
		
		float TargetX = TargetBounds.Min.X + InitialCameraOffset; // 添加256单位的偏移，让摄像机不会紧贴边界
		// 创建目标位置向量
		FVector TargetLocation(TargetX, FixedCameraY, CameraHeight);
		
		// 直接设置位置，确保移动
		SetActorLocation(TargetLocation);
		
	}
}

// 修改SetupLayerBounds方法，添加更多日志
void ARoguelikeCharacter::SetupLayerBounds(const TArray<FMapLayer>& MapLayers)
{
	LayerBounds.Empty();

	for (int32 i = 0; i < MapLayers.Num(); ++i)
	{
		const FMapLayer& CurrentLayer = MapLayers[i];
        
		// 初始化最小和最大X坐标
		float MinX = MAX_flt;
		float MaxX = -MAX_flt;
		bool bHasValidNode = false;
        
		// 遍历当前层的所有列，找出最小和最大X坐标
		for (const FMapColumn& Column : CurrentLayer.Columns)
		{
			for (const AMapNode* Node : Column.Nodes)
			{
				if (Node)
				{
					float NodeX = Node->GetActorLocation().X;
					MinX = FMath::Min(MinX, NodeX);
					MaxX = FMath::Max(MaxX, NodeX);
					bHasValidNode = true;
				}
			}
		}
        
		// 如果该层有有效节点，设置边界
		if (bHasValidNode)
		{
			// 边界扩展
			MinX -= LeftBoundaryExtension;
			MaxX += RightBoundaryExtension;
            
			// 创建边界盒
			FVector Min(MinX, -500.0f, 0.0f);
			FVector Max(MaxX, 500.0f, CameraHeight * 2);
			FBox LayerBox(Min, Max);
            
			LayerBounds.Add(LayerBox);
			UE_LOG(LogTemp, Warning, TEXT("第%d层边界: X=[%f, %f]"), i, MinX, MaxX);
		}
		else
		{
			// 如果没有节点，使用默认边界
			float xPos = i * 1500.0f;
			FVector Center(xPos, 0, 0);
			FVector Extent(750.0f, 500.0f, 100.0f);
			LayerBounds.Add(FBox(Center - Extent, Center + Extent));
		}
	}
}