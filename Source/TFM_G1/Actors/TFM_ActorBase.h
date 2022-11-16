#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_ActorBase.generated.h"

class ATFM_SwitchFloor;
class UStaticMeshComponent;
UCLASS()
class TFM_G1_API ATFM_ActorBase : public AActor
{
	GENERATED_BODY()

public:
	ATFM_ActorBase();
	
	bool IsMovable();
	UStaticMeshComponent* GetMesh();

protected:
	UPROPERTY(EditAnywhere, Category = "Mobility")
		bool bMovable = false;
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* Mesh = nullptr;

	virtual void BeginPlay() override;
};
