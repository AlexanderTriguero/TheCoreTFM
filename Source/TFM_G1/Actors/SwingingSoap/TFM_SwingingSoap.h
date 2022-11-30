// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_SwingingSoap.generated.h"

class UCableComponent;
class UPhysicsConstraintComponent;

UCLASS()
class TFM_G1_API ATFM_SwingingSoap : public AActor
{
	GENERATED_BODY()
	
public:	
	ATFM_SwingingSoap();
	UPROPERTY(BlueprintReadOnly)
		AActor* AttachEnd = nullptr;
	UPROPERTY(BlueprintReadOnly)
		AActor* AttachStart = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UCableComponent* Cable = nullptr;
	//UPROPERTY(EditDefaultsOnly)
		//UPhysicsConstraintComponent* Constraint = nullptr;
	void SwitchEnd(AActor* newAttachEnd, FName ComponentName);

protected:
	virtual void BeginPlay() override;

private:
	void SetConstraints();

};
