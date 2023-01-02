// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Bubbles/TFM_BubbleBase.h"
#include "Components/SphereComponent.h"
#include "TFM_BubbleElectric.generated.h"

class ATFM_PowerSource;
class UCableComponent;
/**
 * 
 */
UCLASS()
class TFM_G1_API ATFM_BubbleElectric : public ATFM_BubbleBase
{
	GENERATED_BODY()

public:
	ATFM_BubbleElectric();

	UFUNCTION()
		void Connect(ATFM_ActorBase* ConnectTo);
	UFUNCTION()
		void Disconnect();
	UPROPERTY(EditDefaultsOnly)
		UMaterial* ConnectedMaterial = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UMaterial* DisconnectedMaterial = nullptr;
	UPROPERTY(EditDefaultsOnly)
		USphereComponent* ConductionSphere = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UCableComponent* ConductionVisual = nullptr;
	UPROPERTY(EditAnywhere)
		float ConductionRadius;
	UPROPERTY(EditAnywhere)
		bool bIsConnected = false;
	UPROPERTY(EditAnywhere)
		bool bFirstToSource = false; 
	void ConnectToSource(ATFM_PowerSource* ExternalSource, bool SetToConnect);

protected:
	UPROPERTY(EditAnywhere)
		bool bIsConnectedToSource = false;
	void ConnectVisual(AActor* bubbleToConnectTo);
	void DisconnectVisual();
	void CheckConnection();
	void PowerActorsOn();
	virtual void Tick(float DeltaSeconds) override;
	TArray<ATFM_BubbleElectric*> ConnectedBubbles;
	ATFM_BubbleElectric* BubbleConnection = nullptr;
	ATFM_PowerSource* PowerSource = nullptr;
};
