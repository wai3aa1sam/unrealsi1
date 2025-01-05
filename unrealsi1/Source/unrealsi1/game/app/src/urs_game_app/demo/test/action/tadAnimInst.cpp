#include "tadAnimInst.h"

#include "tadCharacter.h"

#include <GameFramework/CharacterMovementComponent.h>

UtadAnimInst::UtadAnimInst()
{

}

void 
UtadAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto* Mesh = GetSkelMeshComponent();
	if (!Mesh) return;

	_character = Cast<AtadCharacter>(Mesh->GetOwner());
	if (!_character) return;

	_updateMove();
	_updateAim();
	_updateSlotWeight();
}

void UtadAnimInst::_updateMove()
{
	auto* ch		= _character.Get();
	auto* charMove	= ch->GetCharacterMovement();

	auto vel = charMove->Velocity;
	vel = ch->GetTransform().InverseTransformVector(vel);
	vel /= charMove->MaxWalkSpeed;

	auto& paState = ch->pawnActionState();
	isCrouch		= paState.isCrouch;
	isJump			= paState.isJump;
	isFall			= charMove->IsFalling();
	isMovingGround	= charMove->IsMovingOnGround();
	isAccelerate	= !charMove->GetCurrentAcceleration().IsZero();
	
	moveForward			= vel.X;
	moveRight			= vel.Y;
	moveSpeed			= vel.Length();
	//stopDirection		= (1.0 - moveSpeed) * vel;
	lastMoveDirection	= vel;

	//URS_DUMP_VAR_INLINE(GetCurrentStateName(0));
	//URS_LOG_INLINE("is Jump: {}, isMovingGround: {}", isJump, isMovingGround);
}

void 
UtadAnimInst::_updateAim()
{
	#if 0
	if (auto* t = _character->Target.Get()) 
	{
		FVector targetLoc = t->GetActorLocation();
		FVector aim		= _character->GetTransform().InverseTransformPosition(targetLoc);
		FRotator rot	= aim.Rotation();
		aimUp    = rot.Pitch;
		aimRight = rot.Yaw;
	} else 
	{
		aimUp    = 0;
		aimRight = 0;
	}
	#endif // 0
}

void 
UtadAnimInst::_updateSlotWeight()
{
	static FName UpperName(TEXT("UpperBody"));
	upperSlotWeight = getMontageSlotWeight(UpperName);
	//upperSlotWeight = GetSlotMontageGlobalWeight(UpperName);

	// using one of them, the value is weird, but not using, then value looks good
	URS_DUMP_VAR_INLINE(upperSlotWeight);
	URS_DUMP_VAR_INLINE(getMontageSlotWeight(UpperName));
	URS_DUMP_VAR_INLINE(GetSlotMontageGlobalWeight(UpperName));
}

float 
UtadAnimInst::getMontageSlotWeight(FName slot)
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
