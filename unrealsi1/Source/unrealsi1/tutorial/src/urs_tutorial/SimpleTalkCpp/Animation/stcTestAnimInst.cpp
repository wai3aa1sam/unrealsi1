#include "stcTestAnimInst.h"
#include "stcTestAnimCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UstcTestAnimInst::UstcTestAnimInst() 
{
}

void UstcTestAnimInst::NativeUpdateAnimation(float DeltaSeconds) 
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto* Mesh = GetSkelMeshComponent();
	if (!Mesh) return;

	MyCharacter = Cast<AstcTestAnimCharacter>(Mesh->GetOwner());
	if (!MyCharacter) return;

	_UpdateMove();
	_UpdateAim();
	_UpdateSlotWeight();
}

void UstcTestAnimInst::_UpdateMove() 
{
	auto* charMove = MyCharacter->GetCharacterMovement();

	auto vel = charMove->Velocity;
	vel = MyCharacter->GetTransform().InverseTransformVector(vel);

	vel /= charMove->MaxWalkSpeed;

	MoveForward = vel.X;
	MoveRight   = vel.Y;

	MyCrouch = MyCharacter->MyCrouch;

	IsMovingGround = charMove->IsMovingOnGround();
}

void UstcTestAnimInst::_UpdateAim() 
{
	if (auto* t = MyCharacter->Target.Get()) 
	{
		FVector targetLoc = t->GetActorLocation();
		FVector aim = MyCharacter->GetTransform().InverseTransformPosition(targetLoc);
		FRotator rot = aim.Rotation();
		//AimUp    = rot.Pitch;
		//AimRight = rot.Yaw;
	} else {
		AimUp    = 0;
		AimRight = 0;
	}
}

void UstcTestAnimInst::_UpdateSlotWeight() 
{
	static FName UpperName(TEXT("Upper"));
	UpperSlotWeight = GetMontageSlotWeight(UpperName);
	//GetSlotMontageGlobalWeight();
}

float UstcTestAnimInst::GetMontageSlotWeight(FName slot) 
{
	float outWeight = 0;

	int32 const NumInstances = MontageInstances.Num();

	for (int32 InstanceIndex = NumInstances - 1; InstanceIndex >= 0; InstanceIndex--) 
	{
		const FAnimMontageInstance* MontageInstance = MontageInstances[InstanceIndex];
		if (!MontageInstance || !MontageInstance->IsActive()) continue;
		if (!MontageInstance->Montage->IsValidSlot(slot)) continue;
		outWeight += MontageInstance->GetWeight();
	}

	outWeight = FMath::Clamp(outWeight, 0.0f, 1.0f);
	return outWeight;
}