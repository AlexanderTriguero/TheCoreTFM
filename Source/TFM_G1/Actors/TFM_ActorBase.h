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
	USceneComponent* GetRootPoint();
	virtual void ApplyForce(FVector Direction,float Force, int PushAttracValue);
	
	UPROPERTY(EditAnywhere, Category = "Mobility")
		bool bLevelAsset = false;
	UPROPERTY(EditAnywhere, Category = "Mobility")
		USceneComponent* RootPoint = nullptr;
	virtual void EnablePhysics();
	virtual void DisablePhysics();


	/* Metodos para modificar fisicas
	virtual bool GetIsIsMoving();
	virtual void SetIsMoving(bool NewIsMoving);
	*/

protected:
	UPROPERTY(EditAnywhere, Category = "Mobility")
		bool bMovable = false;
	UPROPERTY(EditAnywhere, Category = "Mesh")
		UStaticMeshComponent* Mesh = nullptr;

	/* Variables utilizadas para modifcar las fisicas
	bool IsMoving=false;
	bool IsFalling = false;
	*/

	virtual void BeginPlay() override;
};
