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
    if (CachedCharacter)
    {
        // 获取当前摄像机位置
        FVector CurrentLocation = CachedCharacter->GetCameraLocation();
        
        // 限制X坐标在指定范围内
        if (CurrentLocation.X < MinCameraX)
        {
            CurrentLocation.X = MinCameraX;
            CachedCharacter->SetCameraLocation(CurrentLocation);
        }
        else if (CurrentLocation.X > MaxCameraX)
        {
            CurrentLocation.X = MaxCameraX;
            CachedCharacter->SetCameraLocation(CurrentLocation);
        }
    }
}
