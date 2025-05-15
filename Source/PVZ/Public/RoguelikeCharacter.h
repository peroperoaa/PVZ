// RoguelikeCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoguelikeCharacter.generated.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraHeight = 1000.0f;

	// 摄像机固定的Y轴位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float FixedCameraY = 0.0f;

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