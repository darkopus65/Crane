/*
 * Реазилазция методов класса блока
*/

#include "A_Block.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "P_Crane.h"

// Sets default values
AA_Block::AA_Block()
{
	// Создаем блок
	BlockComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockComp"));
	BlockComp->SetSimulatePhysics(true);
	BlockComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BlockComp->SetCollisionObjectType(ECC_PhysicsBody);
	BlockComp->SetCollisionResponseToAllChannels(ECR_Block);
	BlockComp->SetNotifyRigidBodyCollision(true);
	BlockComp->OnComponentHit.AddDynamic(this, &AA_Block::OnCompHit);
	RootComponent = BlockComp;

	// Задаем координаты
	Coords.Append({ FVector(80.0f, 80.0f, 27.0f), FVector(80.0f, -80.0f, 27.0f), FVector(-80.0f, -80.0f, 27.0f), FVector(-80.0f, 80.0f, 27.0f)});

	// Настраиваем Physics Constraint
	constraintInstance.SetLinearXLimit(LCM_Limited, 30);
	constraintInstance.SetLinearYLimit(LCM_Limited, 30);
	constraintInstance.SetLinearZLimit(LCM_Limited, 30);

	constraintInstance.ProfileInstance.LinearLimit.bSoftConstraint = true;
	constraintInstance.ProfileInstance.LinearLimit.Stiffness = 1000;
	constraintInstance.ProfileInstance.LinearLimit.Damping = 4;

	constraintInstance.SetAngularSwing1Limit(ACM_Limited, 40);
	constraintInstance.SetAngularSwing2Limit(ACM_Limited, 40);
	constraintInstance.SetAngularTwistLimit(ACM_Limited, 40);

	constraintInstance.ProfileInstance.TwistLimit.bSoftConstraint = true;
	constraintInstance.ProfileInstance.TwistLimit.Stiffness = 2000;
	constraintInstance.ProfileInstance.TwistLimit.Damping = 2;

	constraintInstance.ProfileInstance.AngularDrive.AngularDriveMode = EAngularDriveMode::TwistAndSwing;
	constraintInstance.ProfileInstance.AngularDrive.SwingDrive.bEnableVelocityDrive = true;
	constraintInstance.ProfileInstance.AngularDrive.TwistDrive.bEnableVelocityDrive = true;
}

// Called when the game starts or when spawned
void AA_Block::BeginPlay()
{
	Super::BeginPlay();
}

void AA_Block::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AP_Crane* crane = Cast<AP_Crane>(OtherActor);

	// Если кран захватыывает блок, создаем с крюком связь
	if (crane && !crane->WasCapture)
	{
		for (size_t i = 0; i < 4; ++i)
		{
			PhysicsComps.Add(NewObject<UPhysicsConstraintComponent>(this));
			PhysicsComps[i]->SetupAttachment(BlockComp);
			PhysicsComps[i]->RegisterComponent();
			PhysicsComps[i]->SetWorldLocation(this->GetActorLocation() + Coords[i]);
			PhysicsComps[i]->ConstraintInstance = constraintInstance;
			PhysicsComps[i]->SetConstrainedComponents(BlockComp, FName(), Cast<UPrimitiveComponent>(crane->GetDefaultSubobjectByName(TEXT("MeshForHookComp"))), FName());
			crane->CurrentVelocity = -2.0f;
			crane->CurrentRate = 0.1f;
			crane->TransformCrane(1.0f);
		}
		crane->WasCapture = true;
		crane->block = this;
	}
}

void AA_Block::ReleaseThis()
{
	// Удаляем все Physics Constraint
	for(UPhysicsConstraintComponent* var : PhysicsComps)
	{
		var->DestroyComponent();
		delete var;
	}
	PhysicsComps.Empty();
}

