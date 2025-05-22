// NodeConnection.cpp

#include "NodeConnection.h"
#include "MapNode.h"

ANodeConnection::ANodeConnection()
{
    PrimaryActorTick.bCanEverTick = false;
    
    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    RootComponent = SplineComponent;
    
    // 设置默认的连接线宽度和厚度
    SplineComponent->SetClosedLoop(false);
}

void ANodeConnection::SetupConnection(FVector StartPoint, FVector EndPoint)
{
    // 清除旧的样条点
    SplineComponent->ClearSplinePoints(false);
    
    // 添加起点和终点
    SplineComponent->AddSplinePoint(StartPoint, ESplineCoordinateSpace::World, false);
    SplineComponent->AddSplinePoint(EndPoint, ESplineCoordinateSpace::World, false);
    
    // 计算中点，并添加一点随机偏移以使线条更自然
    FVector Midpoint = (StartPoint + EndPoint) * 0.5f;
    float RandomOffset = FMath::RandRange(-20.0f, 20.0f);
    Midpoint.Z += RandomOffset;
    
    // 可选：添加中间点使曲线更平滑
    SplineComponent->AddSplinePoint(Midpoint, ESplineCoordinateSpace::World, false);
    
    // 更新样条
    SplineComponent->UpdateSpline();
    
    // 如果有连接网格，创建样条网格组件
    if (ConnectionMesh)
    {
        // 清除旧的样条网格
        for (USplineMeshComponent* MeshComp : SplineMeshes)
        {
            if (MeshComp)
            {
                MeshComp->DestroyComponent();
            }
        }
        SplineMeshes.Empty();
        
        // 为每个样条段添加网格
        for (int32 i = 0; i < SplineComponent->GetNumberOfSplinePoints() - 1; i++)
        {
            USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
            SplineMesh->SetMobility(EComponentMobility::Movable);
            SplineMesh->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);
            
            // 获取样条点位置和切线
            FVector StartPos, StartTangent, EndPos, EndTangent;
            SplineComponent->GetLocationAndTangentAtSplinePoint(i, StartPos, StartTangent, ESplineCoordinateSpace::Local);
            SplineComponent->GetLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent, ESplineCoordinateSpace::Local);
            
            // 配置样条网格
            SplineMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);
            SplineMesh->SetStaticMesh(ConnectionMesh);
            SplineMesh->SetMaterial(0, ConnectionMaterial);
            
            // 设置网格大小（可根据需求调整）
            SplineMesh->SetStartScale(FVector2D(0.5f, 0.5f));
            SplineMesh->SetEndScale(FVector2D(0.5f, 0.5f));
            
            SplineMesh->RegisterComponent();
            SplineMeshes.Add(SplineMesh);
        }
    }
}

void ANodeConnection::SetActive(bool bActive)
{
    // 根据激活状态更改材质
    UMaterialInterface* MaterialToUse = bActive ? ActiveConnectionMaterial : ConnectionMaterial;
    
    if (MaterialToUse)
    {
        for (USplineMeshComponent* MeshComp : SplineMeshes)
        {
            if (MeshComp)
            {
                MeshComp->SetMaterial(0, MaterialToUse);
            }
        }
    }
}