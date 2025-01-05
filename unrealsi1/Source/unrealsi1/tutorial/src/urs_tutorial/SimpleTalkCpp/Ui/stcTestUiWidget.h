#pragma once

#include "urs_tutorial/common/urs_tutorial_common.h"

#include <Blueprint/UserWidget.h>
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/ListView.h>

#include "stcTestUiWidget.generated.h"

UCLASS()
class UNREALSI1_API UstcTestUiWidget : public UUserWidget {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Transient, meta=(BindWidget)) UTextBlock*	MyTextBlock	= nullptr;
	UPROPERTY(EditAnywhere, Transient, meta=(BindWidget)) UButton*		MyButton	= nullptr;
	UPROPERTY(EditAnywhere, Transient, meta=(BindWidget)) UListView*	MyListView	= nullptr;

	UPROPERTY(EditAnywhere, Transient, meta=(BindWidgetAnim)) class UWidgetAnimation* stcTestUiAnim = nullptr;

public:
	UstcTestUiWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void OnButtonPressed();

	int _Count = 0;
};

UCLASS()
class UNREALSI1_API UstcTestUiListItemData : public UObject {
	GENERATED_BODY()
public:
	int testInt = 0;
};

UCLASS()
class UNREALSI1_API UstcTestUiListItemWidget : public UUserWidget, public IUserObjectListEntry {
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere, Transient, meta=(BindWidget)) UTextBlock*	MyItemText = nullptr;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};