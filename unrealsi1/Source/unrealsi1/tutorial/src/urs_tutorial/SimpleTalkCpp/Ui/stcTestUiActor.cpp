#include "stcTestUiActor.h"

#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

#include <UObject/ConstructorHelpers.h>

#include "urs_tutorial/common/urs_tutorial_common.h"

AstcTestUiActor::AstcTestUiActor()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube'"));
	MeshComponent->SetStaticMesh(MeshObj.Object);


	//WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent = ursActorUtil::newAttachComponent_Ctor<UWidgetComponent>(this, MeshComponent);

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/tutorial/SimpleTalkCpp/Ui/stcWBp_TestUiWorldSp'"));
	WidgetComponent->SetWidgetClass(WidgetClass.Class);
	WidgetComponent->SetRelativeLocation(FVector(0, 0, 130));
}
