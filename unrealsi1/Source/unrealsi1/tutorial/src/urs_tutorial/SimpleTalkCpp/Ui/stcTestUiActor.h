#pragma once

#include <GameFramework/Actor.h>
#include "stcTestUiActor.generated.h"

class UWidgetComponent;
class UStaticMeshComponent;

UCLASS()
class UNREALSI1_API AstcTestUiActor : public AActor 
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> MeshComponent = nullptr;
	UPROPERTY(VisibleAnywhere) TObjectPtr<UWidgetComponent>		WidgetComponent = nullptr;
	
public:
	AstcTestUiActor();
};