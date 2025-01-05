#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "Animation/SkeletalMeshActor.h"

#include "stcTestBasicAnimInst.generated.h"

UCLASS()
class UNREALSI1_API AstcTestBasicAnimActor : public ASkeletalMeshActor {
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere) float testBlend = 0.5f;

};


UCLASS()
class UNREALSI1_API UstcTestBasicAnimInst : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) float testBlend = 0.5f;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
