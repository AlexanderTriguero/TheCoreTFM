// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFM_WeaponWidget.generated.h"

class UVerticalBox;
class UImage;
UCLASS()
class TFM_G1_API UTFM_WeaponWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:


	/*UPROPERTY(EditAnywhere, meta = (BindWidget))
		UImage* BubbleImage4;*/

	//Binding Widget nos obliga a crear un UWidget con este nombre y del mismo tipo
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UVerticalBox* BubbleVerticalBox=nullptr;

	void CreateBubble();
	void DeleteBubble();

protected:
	virtual void NativeConstruct() override;
private:
	int CreateableBubles = 4;
	int MaxBublles = 4;
};
