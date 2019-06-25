/*
 * ����������� ������� ������ ���������� �����
*/
#include "P_Crane.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Camera/CameraComponent.h"
#include "A_Block.h"
#include "DrawDebugHelpers.h"

// Sets default values
<<<<<<< HEAD
AP_Crane::AP_Crane() : SpeedOfTurnUpAndDown(30), SpeedOfTurnAtRate(7), ZLimited(0)
=======
AP_Crane::AP_Crane() : ZLimited(0), SpeedOfTurnUpAndDown(30), SpeedOfTurnAtRate(30)
>>>>>>> 118af87... add lines and fix block
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������� ��������� 
	MeshForPlatformComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshForPlatformComp"));
	MeshForPlatformComp->SetSimulatePhysics(true);
	MeshForPlatformComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	MeshForPlatformComp->SetCollisionObjectType(ECC_Pawn);
	MeshForPlatformComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshForPlatformComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	

	RootComponent = MeshForPlatformComp;

	// ������� ���� ��������
	MeshForShoulderComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshForShoulderComp"));
	MeshForShoulderComp->SetupAttachment(RootComponent);

	// ������� ���� �����
	MeshForHandComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshForHandComp"));
	MeshForHandComp->SetCollisionResponseToAllChannels(ECR_Block);
	MeshForHandComp->SetCollisionObjectType(ECC_WorldDynamic);
	MeshForHandComp->SetupAttachment(MeshForShoulderComp);

	// ������� ��������� ��� �������
	MeshForBaseComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshForBaseComp"));
	MeshForBaseComp->SetCollisionResponseToAllChannels(ECR_Block);
	MeshForBaseComp->SetCollisionObjectType(ECC_WorldDynamic);
	MeshForBaseComp->SetupAttachment(MeshForHandComp);

	// ������� ����
	MeshForHookComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshForHookComp"));
	MeshForHookComp->SetSimulatePhysics(true);
	MeshForHookComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshForHookComp->SetCollisionObjectType(ECC_PhysicsBody);
	MeshForHookComp->SetCollisionResponseToAllChannels(ECR_Block);
	MeshForHookComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);
	MeshForHookComp->SetupAttachment(MeshForHandComp);

	// ������ ��������� ��� Physics constraint 
	FConstraintInstance constraintInstance;
	constraintInstance.SetLinearXLimit(LCM_Limited, ZLimited);
	constraintInstance.SetLinearYLimit(LCM_Limited, ZLimited);
	constraintInstance.SetLinearZLimit(LCM_Limited, ZLimited);

	constraintInstance.ProfileInstance.LinearLimit.bSoftConstraint = true;
	constraintInstance.ProfileInstance.LinearLimit.Stiffness = 2000;
	constraintInstance.ProfileInstance.LinearLimit.Damping = 4;

	constraintInstance.SetAngularSwing1Limit(ACM_Limited, 40);
	constraintInstance.SetAngularSwing2Limit(ACM_Limited, 40);
	constraintInstance.SetAngularTwistLimit(ACM_Limited, 40);

	constraintInstance.ProfileInstance.AngularDrive.SwingDrive.Stiffness = 2000;
	constraintInstance.ProfileInstance.AngularDrive.SwingDrive.Damping = 2;

	constraintInstance.ProfileInstance.TwistLimit.bSoftConstraint = true;
	constraintInstance.ProfileInstance.TwistLimit.Stiffness = 2000;
	constraintInstance.ProfileInstance.TwistLimit.Damping = 2;

	constraintInstance.ProfileInstance.AngularDrive.AngularDriveMode = EAngularDriveMode::TwistAndSwing;
	constraintInstance.ProfileInstance.AngularDrive.SwingDrive.bEnableVelocityDrive = true;
	constraintInstance.ProfileInstance.AngularDrive.TwistDrive.bEnableVelocityDrive = true;

	// ������� Physics Constraint 
	PhysicsComp = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsComp"));
	PhysicsComp->SetupAttachment(RootComponent);
	PhysicsComp->ConstraintInstance = constraintInstance;
	PhysicsComp->SetConstrainedComponents(MeshForBaseComp, FName(), MeshForHookComp, FName());


	// ������� ������
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(MeshForPlatformComp); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}


void AP_Crane::TurnUpAndDown(float Value)
{
	CurrentVelocity = Value * SpeedOfTurnUpAndDown;
}

void AP_Crane::TurnAtRate(float Rate)
{
	CurrentRate = Rate * SpeedOfTurnAtRate;
}

void AP_Crane::Release()
{
	if (block)
	{
		block->ReleaseThis();
		WasCapture = false;
		block = nullptr;
	}
}

// Called when the game starts or when spawned
void AP_Crane::BeginPlay()
{
	Super::BeginPlay();
<<<<<<< HEAD
	// ������ ����� (� ������������ GEngine ��� �� �������������)
	MeshForPlatformComp->SetMassOverrideInKg(NAME_None, 2000);
	MeshForHookComp->SetMassOverrideInKg(NAME_None, 100);

=======
>>>>>>> 118af87... add lines and fix block
	ZLimited = MinLimit;
	PhysicsComp->SetLinearZLimit(LCM_Limited, ZLimited);
}

// Called every frame
void AP_Crane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TransformCrane(DeltaTime);
}

// Called to bind functionality to input
void AP_Crane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("TurnUpAndDown", this, &AP_Crane::TurnUpAndDown);
	PlayerInputComponent->BindAxis("TurnAtRate", this, &AP_Crane::TurnAtRate);

	PlayerInputComponent->BindAction("Release", IE_Pressed, this, &AP_Crane::Release);
}

void AP_Crane::TransformCrane(float DeltaTime)
{
	// ��������� ��������� �� ��������� �����
	if (CurrentVelocity != 0)
	{
		ZLimited = ZLimited + CurrentVelocity * DeltaTime < MinLimit ? ZLimited : ZLimited + CurrentVelocity * DeltaTime;
		PhysicsComp->SetLinearZLimit(LCM_Limited, ZLimited);
	}

	// ��������� ��������� � ��������� �����
	if (CurrentRate != 0)
	{
		FRotator current = MeshForShoulderComp->GetComponentRotation();
		FRotator NewRotation = FRotator(current.Pitch, current.Yaw + CurrentRate * DeltaTime, current.Roll);

		FQuat QuatRotation = FQuat(NewRotation);

		MeshForShoulderComp->SetRelativeRotation(QuatRotation, true, 0, ETeleportType::None);
	}

	// ������ ���� ��� ������������� 
	if (block)
	{
		for (UPhysicsConstraintComponent* var : block->PhysicsComps)
		{
			DrawDebugLine(GetWorld(), MeshForHookComp->GetComponentToWorld().GetLocation(), var->GetComponentLocation(), FColor::Red);
		}
	}
}

