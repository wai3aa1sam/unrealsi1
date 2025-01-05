#include "stcTestAnimNotify_Fire.h"
#include "stcTestAnimCharacter.h"

void UstcTestAnimNotify_Fire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) 
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp) return;
	auto* ch = Cast<AstcTestAnimCharacter>(MeshComp->GetOwner());
	if (!ch) return;
	ch->AnimNotify_Fire();
}

