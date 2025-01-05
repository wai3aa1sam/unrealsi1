#pragma once

#include "urs_game_app/common/urs_game_app_common.h"
#include <urs_core/game_framework/pawn_action/ursPawnAction.h>

#include "tadPawnAction.generated.h"

#if 0
#pragma mark --- UtadPawnActionConfigs-Decl ---
#endif // 0
#if 1

UCLASS(BlueprintType)
class UNREALSI1_API UtadPawnActionConfigs : public UursPawnActionConfigs
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) TArray<TObjectPtr<UAnimMontage> > attacks;
};

#endif

#if 0
#pragma mark --- FtadPawnActionState-Decl ---
#endif // 0
#if 1

USTRUCT(BlueprintType)
struct UNREALSI1_API FtadPawnActionState : public FursPawnActionState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) uint8 isRunning			: 1;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) uint8 isCrouch			: 1;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) uint8 isJump				: 1;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) int32 curAtkAnimIdx		= 0;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) uint8 isAttacking			: 1;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) uint8 isPendingNextAttack	: 1;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float upperSlotWeight		= 0;
	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly) float blockMoveCurveValue	= 0;
};

#endif
