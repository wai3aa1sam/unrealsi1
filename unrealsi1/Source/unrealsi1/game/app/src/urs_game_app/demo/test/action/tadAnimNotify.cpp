#include "tadAnimNotify.h"
#include "tadCharacter.h"

#include "tadPlayerController.h"

#if 0
#pragma mark --- UtadAnimNotify-Impl ---
#endif // 0
#if 1

void 
UtadAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) 
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp) return;
	auto* ch = Cast<AtadCharacter>(MeshComp->GetOwner());
	if (!ch) return;

	//ch->commitMontage();

	//ch->comboSystem().commitCombo();
}

#endif

#if 0
#pragma mark --- UtadPawnActionAttack_AnimNotify-Impl ---
#endif // 0
#if 1

void 
UtadPawnActionAttackCommit_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp) return;
	auto* ch = Cast<AtadCharacter>(MeshComp->GetOwner());
	if (!ch) return;

	ch->doNextAttack();
}

void 
UtadPawnActionAttackReset_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp) return;
	auto* ch = Cast<AtadCharacter>(MeshComp->GetOwner());
	if (!ch) return;

	ch->resetActionState();
}

#endif

