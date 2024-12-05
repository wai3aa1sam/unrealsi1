#include "ursUiWidget.h"

#include <Blueprint/SlateBlueprintLibrary.h>
#include <Blueprint/WidgetLayoutLibrary.h>

#if 0
#pragma mark --- UursUiWidget-Impl ---
#endif // 0
#if 1

UursUiWidget::UursUiWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    
}

void 
UursUiWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
}

void 
UursUiWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

}

void 
UursUiWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    //USlateBlueprintLibrary::

    auto mouseAbsPos    = UWidgetLayoutLibrary::GetMousePositionOnPlatform();
    auto mouseVpPos     = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

    URS_LOG_INLINE("mouseAbsPos: {}", mouseAbsPos);
    URS_LOG_INLINE("mouseVpPos: {}", mouseVpPos);


}

#endif