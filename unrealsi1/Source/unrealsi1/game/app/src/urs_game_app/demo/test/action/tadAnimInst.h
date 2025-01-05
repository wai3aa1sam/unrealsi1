#pragma once

#include "urs_game_app/common/urs_game_app_common.h"

#include <Animation/AnimInstance.h>
#include "tadAnimInst.generated.h"

class AtadCharacter;
class UAnimSequence;

UCLASS()
class UNREALSI1_API UtadAnimInst : public UAnimInstance 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float moveForward		= 0;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float moveRight		= 0;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float moveSpeed		= 0;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) bool	isJump			= false;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) bool	isFall			= false;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) bool	isMovingGround	= true;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) bool	isCrouch		= false;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) bool	isAccelerate	= false;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float aimUp			= 0;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float aimRight		= 0;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float upperSlotWeight = 0;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) FVector lastMoveDirection;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) FVector stopDirection;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float	yawDelta		= 0.0f;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) bool	isIdle			= false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UAnimSequence> upperAnimSeq;


	UPROPERTY(VisibleAnywhere, Transient) TObjectPtr<AtadCharacter> _character;

	/*UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) bool isAttackA = false;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) bool isAttackB = false;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) bool isAttackC = false;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) uint8 isAttackD : 1;*/


public:
	UtadAnimInst();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	void _updateMove();
	void _updateAim();
	void _updateSlotWeight();

	float getMontageSlotWeight(FName slot);
};