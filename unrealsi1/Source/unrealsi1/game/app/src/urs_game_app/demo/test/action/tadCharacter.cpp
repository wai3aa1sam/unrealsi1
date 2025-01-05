#include "tadCharacter.h"

#include "tadAnimInst.h"
#include "tadPlayerController.h"

#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <Engine/SkeletalMeshSocket.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>

#include <UObject/UnrealTypePrivate.h>

#if 0
#pragma mark --- AtadCharacter-Impl ---
#endif // 0
#if 1

AtadCharacter::AtadCharacter()
{
	URS_CDO_FINDER(_inputMapCtx,		"/Script/EnhancedInput.InputMappingContext'/Game/demo/test/action/input/tadCharacter_ImCtx'");
	URS_CDO_FINDER(inputActionConfigs,	"/Script/unrealsi1.tadInputActionConfigs'/Game/demo/test/action/input/tadCharacter_IaCfg'");
	URS_CDO_FINDER(comboConfigs,		"/Script/unrealsi1.tadComboConfigs'/Game/demo/test/action/combo/prgGreystone_ComboCfgs'");
	URS_CDO_FINDER(pawnActionConfigs,	"/Script/unrealsi1.tadPawnActionConfigs'/Game/demo/test/action/pawn_action/prgGreystone_PaCfgs'");
	
	USkinnedAsset* skinnedAsset = nullptr;
	URS_CDO_FINDER(skinnedAsset,		"/Script/Engine.SkeletalMesh'/Game/import/char/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone'");
	GetMesh()->SetSkinnedAsset(skinnedAsset);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -97), FRotator(0, 270, 0));
	
	// AnimBP
	URS_CDC_FINDER(GetMesh()->AnimClass, "/Script/Engine.AnimBlueprint'/Game/demo/char/prg_greystone/prgGreystone_AnimBp'");

	// Create a camera boom (pulls in towards the player if there is a collision)
	auto* CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	auto* FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Character Movement
	bUseControllerRotationYaw = true;

	auto* charMove = GetCharacterMovement();
	charMove->bOrientRotationToMovement	= true; // Character moves in the direction of input...	
	charMove->RotationRate				= FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	charMove->JumpZVelocity				= 600.f;
	charMove->AirControl				= 0.2f;
	charMove->MaxWalkSpeed				= 225 * 3;

	auto* capsComp = GetCapsuleComponent();
	capsComp->InitCapsuleSize(42.f, 96.0f);
}

void
AtadCharacter::BeginPlay()
{
	Super::BeginPlay();

	_comboSys = NewObject<UursComboSystem>(this);
	comboSystem().setComboConfigs(comboConfigs.Get(), this, &ThisClass::resetCombo);
}

void AtadCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//comboSystem().update(DeltaSeconds, this);

	URS_LOG("TEST");
}

void 
AtadCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* PlayerController	= Cast<APlayerController>(GetController());
	auto* Subsystem			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(_inputMapCtx, 0);
}

void 
AtadCharacter::combo_Attack(const UursComboSet* comboSet)
{
	/*bool isOverrideActionState = false;

	const auto& mtgs		= comboSet->montages;
	const auto	mtgAtkSize	= mtgs.Num();

	check(mtgAtkSize > 0);
	if (!isAttacking || comboSystem().getComboState() == EursComboSystemState::Commit) 
	{
		isAttacking = true;

		auto atkMtgIdx = curAtkMontageIdx;
		curAtkMontageIdx = (curAtkMontageIdx + 1) % mtgAtkSize;

		URS_LOG("doAttack {}", atkMtgIdx);
		auto& mtgAtk = mtgs[atkMtgIdx];
		playMontage(mtgAtk);
	}
	else
	{
		comboSystem().setPendingComboSet(comboSet);
		isPendingNextAttack = true;
	}*/
}

void 
AtadCharacter::resetCombo()
{
	
}

void 
AtadCharacter::resetActionState()
{
	auto& state = _paState;
	state.isAttacking			= false;
	state.isPendingNextAttack	= false;
	state.curAtkAnimIdx			= 0;
}

void
AtadCharacter::doJump()
{
	pawnActionState().isJump = true;
	Jump();
}

void
AtadCharacter::doStopJump()
{
	pawnActionState().isJump = false;
	StopJumping();
}

void 
AtadCharacter::doAttack()
{
	auto& state = _paState;
	if (!state.isAttacking) 
	{
		_doAttack();
	}
	else
	{
		state.isPendingNextAttack = true;
	}
}

void 
AtadCharacter::doNextAttack()
{
	auto& state = _paState;
	if (state.isPendingNextAttack)
	{
		_doAttack();
		state.isPendingNextAttack = false;
	}
}

void 
AtadCharacter::_doAttack()
{
	const auto& paCfgs		= pawnActionConfigs;
	const auto& mtgAtks		= paCfgs->attacks;
	const auto  mtgAtkSize	= paCfgs->attacks.Num();

	auto& state = _paState;
	state.isAttacking = true;

	auto atkMtgIdx = state.curAtkAnimIdx;
	state.curAtkAnimIdx = (state.curAtkAnimIdx + 1) % mtgAtkSize;

	auto& mtgAtk = mtgAtks[atkMtgIdx];
	playMontage(mtgAtk);
}

void 
AtadCharacter::playMontage(UAnimMontage* animMtg)
{
	auto* animInst = GetMesh()->GetAnimInstance();
	if (!animInst) return;
	animInst->Montage_Play(animMtg);
}

#endif

