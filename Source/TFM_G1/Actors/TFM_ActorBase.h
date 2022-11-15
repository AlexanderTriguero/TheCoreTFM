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
	virtual void ApplyForce(FVector Direction,float Force, int PushAttracValue);
	virtual void EnablePhysics();
	virtual void DisablePhysics();

	virtual bool GetIsIsMoving();
	virtual void SetIsMoving(bool NewIsMoving);

protected:
	UPROPERTY(EditAnywhere, Category = "Mobility")
		bool bMovable = false;
	UPROPERTY(EditAnywhere, Category = "Mobility")
		UStaticMeshComponent* Mesh = nullptr;

	bool IsMoving=false;

	virtual void BeginPlay() override;
};
