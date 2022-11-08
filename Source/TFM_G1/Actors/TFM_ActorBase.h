// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_ActorBase.generated.h"

class UStaticMeshComponent;
UCLASS()
class TFM_G1_API ATFM_ActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATFM_ActorBase();
	virtual void Tick(float DeltaTime) override;

	bool IsMovable();
	UStaticMeshComponent* GetMesh();

protected:
	UPROPERTY(EditAnywhere, Category= "Mobility")
		bool bMovable = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* Mesh =nullptr;

	virtual void BeginPlay() override;
};
