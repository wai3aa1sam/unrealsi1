#include "stcTestAnimCharacter.h"
#include "stcTestAnimInst.h"

#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <Engine/SkeletalMeshSocket.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/SpringArmComponent.h>

#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>

AstcTestAnimBullet::AstcTestAnimBullet() 
	: Speed(100)
	, SimPhysicTime(3)
	, Lifespan(5)
{
	PrimaryActorTick.bCanEverTick = true;

	static FName MeshComponentName("Mesh");
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(MeshComponentName);
	SetRootComponent(MeshComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube'"));
	MeshComponent->SetStaticMesh(MeshObj.Object);
	MeshComponent->SetRelativeScale3D(FVector::OneVector * 0.25f);

	MeshComponent->SetMobility(EComponentMobility::Movable);
}

void AstcTestAnimBullet::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);
	_lifeTime += DeltaSeconds;

	if (_lifeTime > Lifespan) {
		Destroy();
		return;
	}

	if (_lifeTime > SimPhysicTime) {
		MeshComponent->SetSimulatePhysics(true);
		return;
	}

	auto Loc = GetActorLocation();
	Loc += GetActorForwardVector() * (Speed * DeltaSeconds);
	SetActorLocation(Loc);
}

AstcTestAnimCharacter::AstcTestAnimCharacter() 
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("Mesh/Script/Engine.SkeletalMesh'/Game/import/anim/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin'"));
	GetMesh()->SetSkinnedAsset(mesh.Object);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -97), FRotator(0, 270, 0));

	// AnimBP
	static ConstructorHelpers::FClassFinder<UstcTestAnimInst> animBP(TEXT("/Script/Engine.AnimBlueprint'/Game/tutorial/SimpleTalkCpp/Animation/Test/stcTestAnimBp'"));
	GetMesh()->AnimClass = animBP.Class;

	// Character Movement
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 225;

	// Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_Equip_Obj(TEXT("/Script/Engine.AnimMontage'/Game/tutorial/SimpleTalkCpp/Animation/Test/Anim/stcMontage_Equip'"));
	Montage_Equip = Montage_Equip_Obj.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Montage_File_Upper_Obj(TEXT("/Script/Engine.AnimMontage'/Game/tutorial/SimpleTalkCpp/Animation/Test/Anim/stcMontage_Fire_Upper'"));
	Montage_Fire_Upper = Montage_File_Upper_Obj.Object;

	// Bullet
	BulletClass = AstcTestAnimBullet::StaticClass();
}

void AstcTestAnimCharacter::BeginPlay() {
	Super::BeginPlay();

	static FName SpawnBulletSocketName(TEXT("SpawnBulletSocket"));
	SpawnBulletSocket = MyFindSocket(SpawnBulletSocketName);

	static FName AimStartSocketName(TEXT("AimStartSocket"));
	AimStartSocket = MyFindSocket(AimStartSocketName);

	TArray<AActor*> TargetList;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("MyTarget"), TargetList);
	if (TargetList.Num() > 0) {
		Target = TargetList[0];
	}
}


void AstcTestAnimCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	if (auto* ani = GetMesh()->GetAnimInstance()) {
		// MetaData is kind of a curve, but with 1 key only
		static FName BlockMove(TEXT("BlockMove"));
		BlockMoveCurveValue = ani->GetCurveValue(BlockMove);
	}

	if (auto* t = Target.Get()) {
		if (auto* startSock = AimStartSocket.Get()) {
			auto start = startSock->GetSocketLocation(GetMesh());
			auto aim   = t->GetActorLocation();
			DrawDebugLine(GetWorld(), start, aim, FColor::Red);
		}
	}
}

void AstcTestAnimCharacter::MyFire() {
	if (Montage_Fire_Upper) {
		if (auto* ani = GetMesh()->GetAnimInstance()) {
			ani->Montage_Play(Montage_Fire_Upper);
		}
	}
}

void AstcTestAnimCharacter::AnimNotify_Fire() {
	UClass* cls = BulletClass.Get();
	if (!cls) {
		URS_LOG("BulletClass is null");
		return;
	}

	if (auto* sock = SpawnBulletSocket.Get()) {
		FTransform trans = sock->GetSocketTransform(GetMesh());
		trans.SetScale3D(FVector::OneVector);

		if (auto* t = Target.Get()) {
			auto targetLoc = t->GetActorLocation();
			auto v = targetLoc - trans.GetLocation();
			trans.SetRotation(v.Rotation().Quaternion());
		}

		URS_LOG("Spawn Bullet");
		GetWorld()->SpawnActor(cls, &trans);
	}
}

void AstcTestAnimCharacter::MyEquip() {
	URS_LOG("Equip");
	if (Montage_Equip) {

		if (auto* ani = GetMesh()->GetAnimInstance()) 
		{
			ani->Montage_Play(Montage_Equip);
		}
	}
}

const USkeletalMeshSocket* AstcTestAnimCharacter::MyFindSocket(FName name) {
	auto* sock = GetMesh()->GetSocketByName(name);
	if (!sock) {
		URS_LOG("cannot find socket {}", name);
	}
	return sock;
}
