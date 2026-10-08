// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventorySlotWidget.h"
#include "Components/TextBlock.h"

FReply UInventorySlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Double-clicked on Inventory Slot %d"), SlotIndex));
	OnInventorySlotDoubleClicked.Broadcast(SlotIndex);
	return FReply::Handled();
}

void UInventorySlotWidget::SetItemData(UItemDefinition* ItemDefinition, int32 Quantity)
{
	if (ItemIconImage)
	{
		ItemIconImage->SetVisibility(ESlateVisibility::Visible);
		ItemIconImage->SetBrushFromTexture(ItemDefinition->GetItemIcon());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemIconImage is not valid."));
	}

	if (ItemQuantityText && Quantity > 1)
	{
		ItemQuantityText->SetText(FText::FromString(FString::FromInt(Quantity)));
	}
	else if (ItemQuantityText && Quantity <= 1)
	{
		ItemQuantityText->SetText(FText::GetEmpty());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemQuantityText is not valid."));
	}
}

void UInventorySlotWidget::ClearSlot()
{
	if (ItemIconImage)
	{
		ItemIconImage->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemIconImage is not valid."));
	}
	if (ItemQuantityText)
	{
		ItemQuantityText->SetText(FText::GetEmpty());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemQuantityText is not valid."));
	}
}
