// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InteractionPromptWidget.h"

#include "Components/TextBlock.h"

void UInteractionPromptWidget::SetInteractionPrompt(const FText& PromptText)
{
	// Assuming you have a TextBlock named InteractionPromptText in your widget blueprint
	if (InteractionPromptText)
	{
		InteractionPromptText->SetText(PromptText);
	}
}
