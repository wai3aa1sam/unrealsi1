#include "stcTestBasicAnimInst.h"

void UstcTestBasicAnimInst::NativeUpdateAnimation(float DeltaSeconds) 
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto* Mesh = GetSkelMeshComponent();
	if (!Mesh) return;

	auto* Actor = Cast<AstcTestBasicAnimActor>(Mesh->GetOwner());
	if (!Actor) return;

	testBlend = Actor->testBlend;
}
