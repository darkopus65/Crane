/*
 * ����� �����
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Block.generated.h"

class UPhysicsConstraintComponent;

UCLASS()
class CRANE_API AA_Block : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_Block();

protected:

	// ����
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BlockComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ��������� ������������ 
	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


private:
	// ��������� Physics constraint 
	FConstraintInstance constraintInstance;

public:	
	// ������ ��� Physics Constraints 
	TArray<UPhysicsConstraintComponent*> PhysicsComps;

	// ������ ��������� ��� Physics Constraints
	TArray<FVector> Coords;

	// ������ �����
	void ReleaseThis();

};
