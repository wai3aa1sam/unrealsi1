#include "stcTestUiWidget.h"

UstcTestUiWidget::UstcTestUiWidget(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	SetIsFocusable(true);
}

void UstcTestUiWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();
	MyButton->OnPressed.AddDynamic(this, &ThisClass::OnButtonPressed);
}

void UstcTestUiWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	_Count++;

	FString str = ursFormat("TextBlock {}", _Count);
	MyTextBlock->SetText(FText::FromString(str));
}

void UstcTestUiWidget::OnButtonPressed() {
	URS_LOG("OnButtonPressed");

	if (MyListView) {
		UstcTestUiListItemData* item = NewObject<UstcTestUiListItemData>();
		item->testInt = _Count;

		MyListView->AddItem(item);
	}

	if (stcTestUiAnim) 
	{
		PlayAnimation(stcTestUiAnim);
	}
}


void UstcTestUiListItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject) 
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	auto* item = Cast<UstcTestUiListItemData>(ListItemObject);
	if (!item) {
		URS_LOG("Error UstcTestUiListItemData");
		return;
	}

	FString str = ursFormat("ListItem {}", item->testInt);
	MyItemText->SetText(FText::FromString(str));
}

