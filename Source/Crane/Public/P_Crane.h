/*
 * ����� ���������� �����
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "P_Crane.generated.h"

UCLASS()
class CRANE_API AP_Crane : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AP_Crane();

protected:

	// ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	// ��������� � ��������
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshForBaseComp;

	// ���� 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshForHookComp;

	// ��������� ��� �������� 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshForShoulderComp;

	// �������� ��������� ����� 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshForPlatformComp;

	// ��������� ��� "����" ����� 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshForHandComp;

	// Physics Constraint ��� ������ ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UPhysicsConstraintComponent* PhysicsComp;

	// ����� ������� �����
	UPROPERTY(VisibleAnywhere, Category = "Property")
	float MinLimit = 40.0f;

	// �������� ������� �����
	UPROPERTY(EditAnywhere, Category = "Property")
	float SpeedOfTurnUpAndDown;

	// �������� �������� �����
	UPROPERTY(EditAnywhere, Category = "Property")
	float SpeedOfTurnAtRate;
	
	// ������������ �������� ������� ����� 
	void TurnUpAndDown(float Value);

	// ������������ �������� �������� �����
	void TurnAtRate(float Rate);

	// ��������� ���� 
	void Release();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// ������ ������� �����
	float ZLimited;
public:	

	// ��� �� ������ �����
	bool WasCapture;

	// ������� �������
	float CurrentRate;

	// ������� �������� �������
	float CurrentVelocity;

	// ��������� �� ����������� ����
	class AA_Block* block;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ����������� ��������� � ��������� �����
	void TransformCrane(float DeltaTime);

};
