// RouguelikePlayerController.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "RouguelikePlayerController.generated.h"

class ARoguelikeCharacter;
class UInputAction;

/**
 * 控制roguelike地图导航的玩家控制器
 */
UCLASS()
class PVZ_API ARouguelikePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARouguelikePlayerController();

	// 摄像机移动速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraDragSpeed = 2.0f;

	// 摄像机X轴移动范围限制
	UPROPERTY(EditAnywhere, Category = "Camera")
	float MinCameraX = -256.0f;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float MaxCameraX = 5685.0f;

	// 获取并限制摄像机位置的辅助函数
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void ClampCameraPosition();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// 输入映射上下文
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// 鼠标按下输入动作
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MousePressAction;

	// 鼠标释放输入动作
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MouseReleaseAction;

	// 鼠标移动输入动作
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MouseMoveAction;

private:
	// 记录是否正在拖动
	bool bIsDragging;
    
	// 上一次鼠标位置
	FVector2D LastMousePosition;
    
	// 对Character的引用
	UPROPERTY()
	ARoguelikeCharacter* CachedCharacter;

	// 处理鼠标按下事件
	void OnMousePressed(const FInputActionValue& Value);
    
	// 处理鼠标释放事件
	void OnMouseReleased(const FInputActionValue& Value);
    
	// 处理鼠标移动事件
	void OnMouseMoved(const FInputActionValue& Value);
};