#pragma once

#include "urs_tutorial/common/urs_tutorial_common.h"
#include <GameFramework/GameModeBase.h>

#include "stcTestUiPlayerController.generated.h"

class UstcTestUiWidget;

UCLASS()
class UNREALSI1_API AstcTestUiGameMode : public AGameModeBase 
{
	GENERATED_BODY()
public:
	AstcTestUiGameMode();
};

UCLASS()
class UNREALSI1_API AstcTestUiPlayerController : public APlayerController 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)				TSubclassOf<UstcTestUiWidget>	MyWidgetClass;

	UPROPERTY(EditAnywhere, Transient)	TObjectPtr<UstcTestUiWidget>	MyWidget = nullptr;

public:
	AstcTestUiPlayerController();
	virtual void BeginPlay() override;

	void CreateMyWidget();
	void SetCustomNavigationConfig();
};