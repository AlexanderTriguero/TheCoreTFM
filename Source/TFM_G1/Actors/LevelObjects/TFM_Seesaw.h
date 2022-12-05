#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "TFM_Seesaw.generated.h"

UCLASS()
class TFM_G1_API ATFM_Seesaw : public AActor
{
	GENERATED_BODY()
	
public:	
	ATFM_Seesaw();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* SeesawMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* BaseMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics")
		UPhysicsConstraintComponent* SeesawPhysics = nullptr;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
