// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TFM_WeaponWidget.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"

void UTFM_WeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


void UTFM_WeaponWidget::CreateBubble()
{
	if (BubbleVerticalBox) {
		if (CreateableBubles > 0 && BubbleVerticalBox->GetChildAt(CreateableBubles-1)) {
			CreateableBubles = CreateableBubles--;
			BubbleVerticalBox->GetChildAt(CreateableBubles)->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
void UTFM_WeaponWidget::DeleteBubble()
{
	if (BubbleVerticalBox) {
		if (CreateableBubles < MaxBublles && BubbleVerticalBox->GetChildAt(CreateableBubles)) {
			BubbleVerticalBox->GetChildAt(CreateableBubles)->SetVisibility(ESlateVisibility::Visible);
			CreateableBubles = CreateableBubles++;
		}
	}
}




