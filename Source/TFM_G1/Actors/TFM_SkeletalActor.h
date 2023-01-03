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
	void Activate();
	USkeletalMeshComponent* GetMesh();
	UPROPERTY(EditAnywhere, Category = "Switches")
		TArray<ATFM_SwitchFloor*> SwitchList;

protected:
	virtual void Tick(float DeltaSeconds) override;
	/*UPROPERTY(EditAnywhere, Category = "Open State")
		UAnimMontage* AnimStateOpen = nullptr;
	UPROPERTY(EditAnywhere, Category = "Close State")
		UAnimMontage* AnimStateClose = nullptr;*/
	UPROPERTY(EditAnywhere, Category = "Switchable")
		bool bIsSwitchable = false;
	UPROPERTY(EditAnywhere, Category = "Switchable")
		bool bIsActive = false;
	UPROPERTY(EditAnywhere, Category = "Electric")
		bool bIsElectric = false;
	UPROPERTY(EditAnywhere, Category = "Frame")
		UStaticMeshComponent* Frame = nullptr;
	UPROPERTY(EditAnywhere, Category = "Door")
		UStaticMeshComponent* Door = nullptr;
private:
	bool IsConnected();
};
