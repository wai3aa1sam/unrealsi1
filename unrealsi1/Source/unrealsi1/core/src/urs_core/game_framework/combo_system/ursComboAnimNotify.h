#pragma once

#include "../../common/urs_core_common.h"

#include <Animation/AnimNotifies/AnimNotify.h>
#include <Animation/AnimNotifies/AnimNotifyState.h>

#include "ursComboAnimNotify.generated.h"

#if 0
#pragma mark --- UComboBlockState_AnimNotify-Decl ---
#endif // 0
#if 1

UCLASS()
class UursComboBlockState_AnimNotify : public UAnimNotify 
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

#endif

#if 0
#pragma mark --- UComboCommitState_AnimNotify-Decl ---
#endif // 0
#if 1

UCLASS()
class UursComboCommitState_AnimNotify : public UAnimNotify 
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

#endif

#if 0
#pragma mark --- UComboResetState_AnimNotify-Decl ---
#endif // 0
#if 1

UCLASS()
class UursComboResetState_AnimNotify : public UAnimNotify 
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

#endif


#if 0
#pragma mark --- UCombo_AnimNotifyState-Decl ---
#endif // 0
#if 1

UCLASS()
class UursCombo_AnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference) override;
};

#endif