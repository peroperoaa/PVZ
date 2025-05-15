

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoguelikeNodeTypes.h"
#include "Components/WidgetComponent.h"
#include "MapNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNodeActivated, AMapNode*, ActivatedNode);
UCLASS()
class PVZ_API AMapNode : public AActor
{
	GENERATED_BODY()
	// MapNode.h中添加以下内容
	
public:	
	// Sets default values for this actor's properties
	AMapNode();
	
	//节点类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roguelike")
	ERoguelikeNodeTypes NodeType = ERoguelikeNodeTypes::None;

	//节点坐标
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roguelike")
	FIntVector GridCoordinate;

	//是否访问
	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "Roguelike")
	bool bIsVisited = false;
	
	//节点调用委托
	UPROPERTY(BlueprintAssignable, Category = "Roguelike")
	FNodeActivated OnNodeActivated;

	// 可视化组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roguelike")
	USceneComponent* NodeVisualComponent;
	
	// 用于显示图片的Widget组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roguelike")
	UWidgetComponent* NodeWidgetComponent;
	
	//进入节点
	UFUNCTION(BlueprintNativeEvent)
	void EnterNode(APlayerController* PlayerController);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
