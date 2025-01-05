#include "tadPlayerController.h"

#include "tadCharacter.h"
#include "tadAnimInst.h"

#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <Engine/SkeletalMeshSocket.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>

#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <InputMappingContext.h>

#if 0
#pragma mark --- AtadPlayerController-Impl ---
#endif // 0
#if 1

AtadPlayerController::AtadPlayerController()
	: Super()
{
	this->OverridePlayerInputClass = UtadPlayerInput::StaticClass();
}

void 
AtadPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//BaseTurnRate   = 45.f;
	//BaseLookUpRate = 45.f;
}

void 
AtadPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	URS_LOG_INLINE("inputDirection: {}", inputDirection);

	auto* ch = Cast<AtadCharacter>(GetPawn());
	if (!ch) return;

	auto v = ch->GetTransform().TransformVector(inputDirection);
	//v *= FMath::Clamp(1 - 0.0, 0.0f, 1.0f);
	ch->GetMovementComponent()->AddInputVector(v);
	//ch->AddMovementInput();

	// comboSystem().update();
}

void
AtadPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (auto* playerInput = Cast<UtadPlayerInput>(PlayerInput))
	{
		TArray<FKey> pressedKeys;
		playerInput->getPressedKeyTo(&pressedKeys, this);
		URS_LOG_INLINE("PressedKeys: {}", pressedKeys);
	}
}

void 
AtadPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	_character = Cast<AtadCharacter>(aPawn);

	//_character->_inputMapCtx->
	{
		// Axis
		auto* inputCmpn = Cast<UEnhancedInputComponent>(InputComponent);
		auto* ch		= Cast<AtadCharacter>(aPawn);

		if (inputCmpn && ch && ch->inputActionConfigs)
		{
			if (ch->inputActionConfigs->iaMove)		inputCmpn->BindAction(ch->inputActionConfigs->iaMove,	ETriggerEvent::Triggered, this, &AtadPlayerController::onInput_iaMove_Triggered);
			if (ch->inputActionConfigs->iaMove)		inputCmpn->BindAction(ch->inputActionConfigs->iaMove,	ETriggerEvent::Completed, this, &AtadPlayerController::onInput_iaMove_Completed);
			if (ch->inputActionConfigs->iaLook)		inputCmpn->BindAction(ch->inputActionConfigs->iaLook,	ETriggerEvent::Triggered, this, &AtadPlayerController::onInput_iaLook_Triggered);
			if (ch->inputActionConfigs->iaLook)		inputCmpn->BindAction(ch->inputActionConfigs->iaLook,	ETriggerEvent::Completed, this, &AtadPlayerController::onInput_iaLook_Completed);
			if (ch->inputActionConfigs->iaJump)		inputCmpn->BindAction(ch->inputActionConfigs->iaJump,	ETriggerEvent::Triggered, this, &AtadPlayerController::onInput_iaJump_Triggered);
			if (ch->inputActionConfigs->iaJump)		inputCmpn->BindAction(ch->inputActionConfigs->iaJump,	ETriggerEvent::Completed, this, &AtadPlayerController::onInput_iaJump_Completed);
			if (ch->inputActionConfigs->iaCrouch)	inputCmpn->BindAction(ch->inputActionConfigs->iaCrouch,	ETriggerEvent::Triggered, this, &AtadPlayerController::onInput_iaCrouch_Triggered);
			if (ch->inputActionConfigs->iaCrouch)	inputCmpn->BindAction(ch->inputActionConfigs->iaCrouch,	ETriggerEvent::Completed, this, &AtadPlayerController::onInput_iaCrouch_Completed);
			if (ch->inputActionConfigs->iaAttack)	inputCmpn->BindAction(ch->inputActionConfigs->iaAttack,	ETriggerEvent::Triggered, this, &AtadPlayerController::onInput_iaAttack_Triggered);
			if (ch->inputActionConfigs->iaAttack)	inputCmpn->BindAction(ch->inputActionConfigs->iaAttack,	ETriggerEvent::Completed, this, &AtadPlayerController::onInput_iaAttack_Completed);
			
			//inputCmpn->BindAction(ch->inputActionConfig->iaMoveForward, ETriggerEvent::Triggered, this, &AtadPlayerController::onInput_MoveForward);
			//inputCmpn->BindAction(ch->inputActionConfig->iaMoveRight,	ETriggerEvent::Triggered, this, &AtadPlayerController::onInput_MoveRight);
		}
	}
}

void 
AtadPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	_character = nullptr;
}

void
AtadPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	SetShowMouseCursor(true);
	
}

void 
AtadPlayerController::createUiWidget()
{

}

void 
AtadPlayerController::onInput_iaMove_Triggered(const FInputActionInstance& iaInst)
{
	auto v = iaInst.GetValue().Get<FVector2D>();	URS_UNUSED(v);

	inputDirection.X = v.X;
	inputDirection.Y = v.Y;
	//URS_LOG_INLINE("{}: {}", __FUNCTION__, v);
}

void 
AtadPlayerController::onInput_iaMove_Completed(const FInputActionInstance& iaInst)
{
	onInput_iaMove_Triggered(iaInst);

	addComboKey(character(), iaInst);
}

void 
AtadPlayerController::onInput_iaLook_Triggered(const FInputActionInstance& iaInst)
{
	auto v = iaInst.GetValue().Get<FVector2D>();	URS_UNUSED(v);

	AddYawInput(v.X);
	AddPitchInput(-v.Y);
}

void 
AtadPlayerController::onInput_iaLook_Completed(const FInputActionInstance& iaInst)
{
	onInput_iaLook_Triggered(iaInst);
}

void 
AtadPlayerController::onInput_iaJump_Triggered(const FInputActionInstance& iaInst)
{
	if (!character()) return;
	auto* ch = character();

	ch->doJump();
	addComboKey(character(), iaInst);
}

void 
AtadPlayerController::onInput_iaJump_Completed(const FInputActionInstance& iaInst)
{
	if (!character()) return;
	auto* ch = character();

	ch->doStopJump();
}

void 
AtadPlayerController::onInput_iaCrouch_Triggered(const FInputActionInstance& iaInst)
{
	addComboKey(character(), iaInst);
}

void 
AtadPlayerController::onInput_iaCrouch_Completed(const FInputActionInstance& iaInst)
{
	addComboKey(character(), iaInst);
}

#if 0
void 
AtadPlayerController::onInput_iaAttack_Triggered(const FInputActionInstance& iaInst)
{
	if (!character()) return;
	auto* ch = character();
	ch->doAttack();

	static FKey iaAttack = FKey{ TEXT("LeftMouseButton") };		//TODO: remove temp
	ch->comboKeyBuffer.Add(iaAttack);
}

void 
AtadPlayerController::onInput_iaAttack_Completed(const FInputActionInstance& iaInst)
{
}
#endif // 0

void AtadPlayerController::onInput_iaAttack_Triggered(const FInputActionInstance& iaInst)
{
	if (!character()) return;
	auto* ch = character();
	//ch->combo_Attack();

	ch->doAttack();
	//addComboKey(character(), iaInst);
}

void AtadPlayerController::onInput_iaAttack_Completed(const FInputActionInstance& iaInst)
{
	

}

bool AtadPlayerController::isKeyPressed_Attack() const { return _isKeyPressed_Attack; }

AtadCharacter* AtadPlayerController::character() { return _character; }

#endif


#if 0
#pragma mark --- UtadPlayerInput-Impl ---
#endif // 0
#if 1

UtadPlayerInput::UtadPlayerInput()
{

}

#endif