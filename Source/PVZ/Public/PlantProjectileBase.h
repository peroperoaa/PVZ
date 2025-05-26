// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantProjectileBase.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;
class UProjectileMovementComponent;

//子类构造函数需设置ProjectileID然后调用Init()函数
UCLASS()
class PVZ_API APlantProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APlantProjectileBase();
	// Sets default values for this actor's properties

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ProjectileID;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	bool Init();
};
