#pragma once

#include "../common/urs_core_common.h"

#include <GameFramework/PlayerInput.h>
#include <EnhancedPlayerInput.h>

#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <InputMappingContext.h>

#include "ursPlayerInput.generated.h"

#if 0
#pragma mark --- UtadPlayerInput-Decl ---
#endif // 0
#if 1

UCLASS()
class UNREALSI1_API UursPlayerInput : public UEnhancedPlayerInput
{
	GENERATED_BODY()
public:
	UursPlayerInput();
	virtual ~UursPlayerInput();

public:
	void getPressedKeyTo(TArray<FKey>* out, APlayerController* PlayerController);
};

#endif