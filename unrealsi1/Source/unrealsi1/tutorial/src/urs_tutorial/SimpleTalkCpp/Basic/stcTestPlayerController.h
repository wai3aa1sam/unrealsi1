#pragma once

#include "urs_tutorial/common/urs_tutorial_common.h"

#include "stcTestPlayerController.generated.h"

UCLASS()
class AstcTestPlayerController : public APlayerController 
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Transient) FVector InputDirection;

	int CurrentCameraIndex = 0;

public:
	AstcTestPlayerController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;


	void OnInputAxis_MoveForward(float value);
	void OnInputAxis_MoveRight	(float value);

	void OnInputAction_Jump_Pressed();
	void OnInputAction_Jump_Released();
	void OnInputAction_Jump_Axis();
	void OnInputAction_Jump_Repeat();
	void OnInputAction_Jump_DoubleClick();

	void OnInputAction_MyChangeCamera();
	void UpdateCameraTarget();
};