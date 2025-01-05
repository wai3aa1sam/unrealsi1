#pragma once

#include "../common/urs_core_common.h"

#include <Blueprint/UserWidget.h>

#include "ursUiWidget.generated.h"


#if 0
#pragma mark --- UursUiWidget-Decl ---
#endif // 0
#if 1

UCLASS()
class UNREALSI1_API UursUiWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UursUiWidget(const FObjectInitializer& ObjectInitializer);

public:
	virtual void NativePreConstruct() override;

	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};

#endif