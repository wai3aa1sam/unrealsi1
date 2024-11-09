#include "stcTestUiPlayerController.h"

#include <UObject/ConstructorHelpers.h>

#include "stcTestUiWidget.h"
#include "stcTestUiNavigationConfig.h"

AstcTestUiGameMode::AstcTestUiGameMode()
{
	PlayerControllerClass = AstcTestUiPlayerController::StaticClass();
}

AstcTestUiPlayerController::AstcTestUiPlayerController() 
{
	static ConstructorHelpers::FClassFinder<UstcTestUiWidget> cls(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/tutorial/SimpleTalkCpp/Ui/stcWBp_TestUiWidget'"));
	MyWidgetClass = cls.Class;
}

void AstcTestUiPlayerController::BeginPlay() {
	Super::BeginPlay();

	SetShowMouseCursor(true);

	CreateMyWidget();
	FstcTestUiNavigationConfig::Init(this);


}

void AstcTestUiPlayerController::CreateMyWidget() 
{
	if (!MyWidgetClass) {
		URS_LOG("MyWidgetClass is null");
		return;
	}

	MyWidget = CreateWidget<UstcTestUiWidget>(this, MyWidgetClass);
	if (!MyWidget) {
		URS_LOG("Error CreateWidget");
		return;
	}

	MyWidget->AddToViewport();
}