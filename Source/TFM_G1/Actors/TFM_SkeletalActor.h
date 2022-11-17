// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_SkeletalActor.generated.h"

class ATFM_SwitchFloor;
UCLASS()
class TFM_G1_API ATFM_SkeletalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATFM_SkeletalActor();


	void TryActivate();
	void Deactivate();
	USkeletalMeshComponent* GetMesh();
	UPROPERTY(EditAnywhere, Category = "Switches")
		TArray<ATFM_SwitchFloor*> SwitchList;

protected:
	void Activate();
	UPROPERTY(EditAnywhere, Category = "Open State")
		UAnimMontage* AnimStateOpen = nullptr;
	UPROPERTY(EditAnywhere, Category = "Close State")
		UAnimMontage* AnimStateClose = nullptr;
	UPROPERTY(EditAnywhere, Category = "Switchable")
		bool bIsSwitchable = false;
	UPROPERTY(EditAnywhere, Category = "Switchable")
		bool bIsActive = false;
	UPROPERTY(EditAnywhere, Category = "Mesh")
		USkeletalMeshComponent* Mesh = nullptr;
};
