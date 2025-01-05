#pragma once

#include "urs_game_app/common/urs_game_app_common.h"
#include <urs_core/game_framework/ursPlayerController.h>

#include "tadPlayerController.generated.h"

class AtadCharacter;

class UtadTestUiWidget;

class UursComboSystem;

#if 0
#pragma mark --- AtadPlayerController-Decl ---
#endif // 0
#if 1

UCLASS()
class UNREALSI1_API AtadPlayerController : public AursPlayerController 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) TSubclassOf<UtadTestUiWidget> uiWidgetClass;

	UPROPERTY(VisibleAnywhere, Transient) FVector inputDirection;

public:

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)	TObjectPtr<UInputAction> InputMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)	TObjectPtr<UInputAction> InputLook;
	UPROPERTY(EditAnywhere, Category="Input")		TSoftObjectPtr<UInputMappingContext> InputMapping;*/

public:
	AtadPlayerController();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	virtual void PlayerTick(float DeltaTime) override;

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	virtual void SetupInputComponent() override;

public:
	void createUiWidget();

public:
	UFUNCTION() void onInput_iaMove_Triggered(const FInputActionInstance& iaInst);
	UFUNCTION() void onInput_iaMove_Completed(const FInputActionInstance& iaInst);

	UFUNCTION() void onInput_iaLook_Triggered(const FInputActionInstance& iaInst);
	UFUNCTION() void onInput_iaLook_Completed(const FInputActionInstance& iaInst);

	UFUNCTION() void onInput_iaJump_Triggered(const FInputActionInstance& iaInst);
	UFUNCTION() void onInput_iaJump_Completed(const FInputActionInstance& iaInst);

	UFUNCTION() void onInput_iaCrouch_Triggered(const FInputActionInstance& iaInst);
	UFUNCTION() void onInput_iaCrouch_Completed(const FInputActionInstance& iaInst);

	//UFUNCTION() void onInput_iaAttack_Triggered(const FInputActionInstance& iaInst);
	//UFUNCTION() void onInput_iaAttack_Completed(const FInputActionInstance& iaInst);

	UFUNCTION() void onInput_iaAttack_Triggered(const FInputActionInstance& iaInst);
	UFUNCTION() void onInput_iaAttack_Completed(const FInputActionInstance& iaInst);

public:
	bool isKeyPressed_Attack() const;

private:
	uint32_t _isKeyPressed_Attack : 1;

public:
	UPROPERTY(VisibleAnywhere) TObjectPtr<AtadCharacter> _character;

private:
	AtadCharacter* character();

private:
	UPROPERTY(VisibleAnywhere) TObjectPtr<UursComboSystem> _comboSys = nullptr;
};

#endif

#if 0
#pragma mark --- UtadPlayerInput-Decl ---
#endif // 0
#if 1

UCLASS()
class UNREALSI1_API UtadPlayerInput : public UursPlayerInput
{
	GENERATED_BODY()
public:
	UtadPlayerInput();

};

#endif
