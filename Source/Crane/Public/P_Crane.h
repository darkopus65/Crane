/*
 * Класс подъемного крана
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

	// Камера
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	// Компонент с лебедкой
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshForBaseComp;

	// Крюк 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshForHookComp;

	// Компонент для вращения 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshForShoulderComp;

	// Основная платформа крана 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshForPlatformComp;

	// Компонент для "руки" крана 
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshForHandComp;

	// Physics Constraint для физики цепи
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UPhysicsConstraintComponent* PhysicsComp;

	// Лимит подъема крюка
	UPROPERTY(VisibleAnywhere, Category = "Property")
	float MinLimit = 40.0f;

	// Скорость подъема крюка
	UPROPERTY(EditAnywhere, Category = "Property")
	float SpeedOfTurnUpAndDown;

	// Скорость поворота крана
	UPROPERTY(EditAnywhere, Category = "Property")
	float SpeedOfTurnAtRate;
	
	// Подсчитывает значение подъема крюка 
	void TurnUpAndDown(float Value);

	// Подсчитывает значение поворота крана
	void TurnAtRate(float Rate);

	// Отпускаем блок 
	void Release();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Предел подъема крюка
	float ZLimited;
public:	

	// Был ли захват блока
	bool WasCapture;

	// Текущий поворот
	float CurrentRate;

	// Текущая скорость подъема
	float CurrentVelocity;

	// Указатель на захваченный блок
	class AA_Block* block;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Расчитывает изменения в положении крана
	void TransformCrane(float DeltaTime);

};
