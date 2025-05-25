#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoguelikeCharacter.generated.h"

class ARoguelikeMapManager;

UCLASS()
class PVZ_API ARoguelikeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARoguelikeCharacter();

	// 摄像机组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* TopDownCamera;

	// 摄像机高度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", DisplayName = "摄像机高度")
	float CameraHeight = 1000.0f;

	// 摄像机固定的Y轴位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", DisplayName = "摄像机固定Y轴位置")
	float FixedCameraY = 0.0f;

	// 层边界信息
	UPROPERTY(BlueprintReadWrite, Category = "Camera")
	TArray<FBox> LayerBounds;
	
	// 边界左侧扩展量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", DisplayName = "边界左侧扩展")
	float LeftBoundaryExtension = 150.0f;

	// 边界右侧扩展量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", DisplayName = "边界右侧扩展")
	float RightBoundaryExtension = 100.0f;

	// 初始摄像机位置偏移量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", DisplayName = "初始摄像机位置偏移")
	float InitialCameraOffset = 256.0f;

	// 当前层索引
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	int32 CurrentLayerIndex = 0;
	
	// 地图管理器引用
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	ARoguelikeMapManager* MapManager;

	// 移动到指定层
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void MoveToLayer(int32 LayerIndex, float TransitionTime = 1.0f);
 
	// 设置层边界
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetupLayerBounds(const TArray<FMapLayer>& MapLayers);

	// 移动摄像机到指定X位置
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraPositionX(float XPosition);

	// 水平移动摄像机
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void MoveCamera(float XDelta);

	// 获取摄像机当前位置
	UFUNCTION(BlueprintCallable, Category = "Camera")
	FVector GetCameraLocation() const;

	// 设置摄像机位置
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraLocation(const FVector& NewLocation);
	
protected:
	virtual void BeginPlay() override;
};