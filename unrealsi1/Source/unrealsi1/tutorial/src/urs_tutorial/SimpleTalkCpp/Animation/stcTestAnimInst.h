#pragma once

#include <Animation/AnimInstance.h>
#include "stcTestAnimInst.generated.h"

UCLASS()
class UstcTestAnimInst : public UAnimInstance 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float MoveForward = 0;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float MoveRight = 0;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) bool	IsMovingGround = true;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) bool	MyCrouch = false;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float AimUp = 0;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float AimRight = 0;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float UpperSlotWeight = 0;

	UPROPERTY(VisibleAnywhere, Transient) class AstcTestAnimCharacter* MyCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) UAnimSequence* TestAnim = nullptr;


	UstcTestAnimInst();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void _UpdateMove();
	void _UpdateAim();
	void _UpdateSlotWeight();

	float GetMontageSlotWeight(FName slot);
};