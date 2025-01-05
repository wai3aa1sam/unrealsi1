#include "ursComboAnimNotify.h"

#if 0
#pragma mark --- UursComboExecution_AnimNotify-Impl ---
#endif // 0
#if 1

void 
UursComboBlockState_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) 
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp) return;
	/*auto* ch = Cast<AtadCharacter>(MeshComp->GetOwner());
	if (!ch) return;

	ch->comboSystem().setComboSystemState(EursComboSystemState::Block);*/
}

#endif

#if 0
#pragma mark --- UursComboExecution_AnimNotify-Impl ---
#endif // 0
#if 1

void 
UursComboCommitState_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) 
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp) return;
	/*auto* ch = Cast<AtadCharacter>(MeshComp->GetOwner());
	if (!ch) return;
	
	ch->comboSystem().setComboSystemState(EursComboSystemState::Commit);*/
}

#endif

#if 0
#pragma mark --- UursComboResetState_AnimNotify-Impl ---
#endif // 0
#if 1

void 
UursComboResetState_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp) return;
	/*auto* ch = Cast<AtadCharacter>(MeshComp->GetOwner());
	if (!ch) return;

	ch->comboSystem().setComboSystemState(EursComboSystemState::Reset);*/
}

#endif

#if 0
#pragma mark --- UursCombo_AnimNotifyState-Impl ---
#endif // 0
#if 1

void 
UursCombo_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (!MeshComp) return;
	/*auto* ch = Cast<AtadCharacter>(MeshComp->GetOwner());
	if (!ch) return;

	ch->comboSystem().comboBegin();*/
}

void 
UursCombo_AnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if (!MeshComp) return;
	/*auto* ch = Cast<AtadCharacter>(MeshComp->GetOwner());
	if (!ch) return;*/

	//ch->Controller
	//ch->comboSystem().comboUpdate(FrameDeltaTime);
}

void 
UursCombo_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (!MeshComp) return;
	/*auto* ch = Cast<AtadCharacter>(MeshComp->GetOwner());
	if (!ch) return;

	ch->comboSystem().comboEnd();*/
}

#endif

