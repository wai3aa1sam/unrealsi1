#pragma once

#include "urs_core/common/urs_core_common.h"

#include <GameFramework/PlayerController.h>
#include "ursPlayerInput.h"

#include "ursPlayerController.generated.h"

struct FInputActionInstance;

#if 0
#pragma mark --- AtadPlayerController-Decl ---
#endif // 0
#if 1

UCLASS()
class UNREALSI1_API AursPlayerController : public APlayerController 
{
	GENERATED_BODY()
public:
	AursPlayerController();


protected:
	template<class CHARACTER> void addComboKey(CHARACTER* ch, const FInputActionInstance& iaInst);
};

template<class CHARACTER> inline
void 
AursPlayerController::addComboKey(CHARACTER* ch, const FInputActionInstance& iaInst)
{
	if (ch)
		ch->comboSystem().addComboKey(iaInst.GetSourceAction(), iaInst.GetValue());
}

#endif