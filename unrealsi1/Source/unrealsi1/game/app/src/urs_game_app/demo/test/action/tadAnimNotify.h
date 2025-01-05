#pragma once

#include "urs_game_app/common/urs_game_app_common.h"

#include <Animation/AnimNotifies/AnimNotify.h>
#include <Animation/AnimNotifies/AnimNotifyState.h>

#include "tadAnimNotify.generated.h"

#if 0
#pragma mark --- UtadAnimNotify-Decl ---
#endif // 0
#if 1

UCLASS()
class UtadAnimNotify : public UAnimNotify 
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};


#endif

#if 0
#pragma mark --- UtadPawnActionAttack_AnimNotify-Decl ---
#endif // 0
#if 1

UCLASS()
class UtadPawnActionAttackCommit_AnimNotify : public UAnimNotify 
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

UCLASS()
class UtadPawnActionAttackReset_AnimNotify : public UAnimNotify 
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};


#endif