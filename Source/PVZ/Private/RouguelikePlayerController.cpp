// RouguelikePlayerController.cpp
#include "RouguelikePlayerController.h"
#include "RoguelikeCharacter.h" // 确保创建此头文件
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

ARouguelikePlayerController::ARouguelikePlayerController()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
    
    bIsDragging = false;
    LastMousePosition = FVector2D::ZeroVector;
}

void ARouguelikePlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    // 设置输入模式为游戏和UI
    FInputModeGameAndUI InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputMode.SetHideCursorDuringCapture(false);
    SetInputMode(InputMode);
    
    // 添加输入映射上下文
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(InputMappingContext, 0);
    }
    
    // 缓存对Character的引用
    if (GetPawn())
    {
        CachedCharacter = Cast<ARoguelikeCharacter>(GetPawn());
    }
}

void ARouguelikePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    // 获取增强输入组件
    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

    // 绑定鼠标按键事件
    if (MousePressAction)
    {
        EnhancedInputComponent->BindAction(MousePressAction, ETriggerEvent::Started, this, &ARouguelikePlayerController::OnMousePressed);
    }
    if (MouseReleaseAction)
    {
        EnhancedInputComponent->BindAction(MouseReleaseAction, ETriggerEvent::Completed, this, &ARouguelikePlayerController::OnMouseReleased);    }
    if (MouseMoveAction)
    {
        EnhancedInputComponent->BindAction(MouseMoveAction, ETriggerEvent::Triggered, this, &ARouguelikePlayerController::OnMouseMoved);
    }
}

void ARouguelikePlayerController::OnMousePressed(const FInputActionValue& Value)
{
    bIsDragging = true;
    GetMousePosition(LastMousePosition.X, LastMousePosition.Y);
}

void ARouguelikePlayerController::OnMouseReleased(const FInputActionValue& Value)
{
    bIsDragging = false;
}

void ARouguelikePlayerController::OnMouseMoved(const FInputActionValue& Value)
{
    if (bIsDragging && CachedCharacter)
    {
        FVector2D CurrentMousePos;
        GetMousePosition(CurrentMousePos.X, CurrentMousePos.Y);
        
        // 计算鼠标移动距离
        float DeltaX = (CurrentMousePos.X - LastMousePosition.X) * CameraDragSpeed;
        
        // 移动摄像机（只在X轴方向）
        CachedCharacter->MoveCamera(-DeltaX);

        // 确保摄像机在允许范围内
        ClampCameraPosition();
        
        // 更新鼠标位置
        LastMousePosition = CurrentMousePos;
    }
}

void ARouguelikePlayerController::ClampCameraPosition()
{
    if (CachedCharacter && CachedCharacter->LayerBounds.IsValidIndex(CachedCharacter->CurrentLayerIndex))
    {
        // 获取当前层的边界
        FBox CurrentLayerBounds = CachedCharacter->LayerBounds[CachedCharacter->CurrentLayerIndex];
        float MinX = CurrentLayerBounds.Min.X;
        float MaxX = CurrentLayerBounds.Max.X;
        
        // 获取当前摄像机位置
        FVector CurrentLocation = CachedCharacter->GetCameraLocation();
        
        // 打印边界信息用于调试
        UE_LOG(LogTemp, Display, TEXT("摄像机位置X: %f, 当前层边界: [%f, %f]"), 
            CurrentLocation.X, MinX, MaxX);
            
        // 限制X坐标在当前层边界内
        bool bNeedsUpdate = false;
        if (CurrentLocation.X < MinX)
        {
            CurrentLocation.X = MinX;
            bNeedsUpdate = true;
        }
        else if (CurrentLocation.X > MaxX)
        {
            CurrentLocation.X = MaxX;
            bNeedsUpdate = true;
        }
        
        // 仅在需要修正时更新摄像机位置
        if (bNeedsUpdate)
        {
            CachedCharacter->SetCameraPositionX(CurrentLocation.X);
        }
    }
}
