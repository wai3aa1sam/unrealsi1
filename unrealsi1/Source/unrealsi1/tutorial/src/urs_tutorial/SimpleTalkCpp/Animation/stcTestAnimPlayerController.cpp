#include "stcTestAnimPlayerController.h"
#include "stcTestAnimCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>

AstcTestAnimGameMode::AstcTestAnimGameMode() 
{
	PlayerControllerClass = AstcTestAnimPlayerController::StaticClass();
	DefaultPawnClass      = AstcTestAnimCharacter::StaticClass();
}

void AstcTestAnimPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	BaseTurnRate   = 45.f;
	BaseLookUpRate = 45.f;

	auto* ch = Cast<AstcTestAnimCharacter>(GetPawn());
	if (!ch) return;

	auto v = ch->GetTransform().TransformVector(InputDirection);

	v *= FMath::Clamp(1 - ch->BlockMoveCurveValue, 0.0f, 1.0f);

	ch->GetMovementComponent()->AddInputVector(v);
}

void AstcTestAnimPlayerController::OnPossess(APawn* aPawn) {
	Super::OnPossess(aPawn);
	MyCharacter = Cast<AstcTestAnimCharacter>(aPawn);
}

void AstcTestAnimPlayerController::OnUnPossess() {
	MyCharacter = nullptr;
	Super::OnUnPossess();
}

void AstcTestAnimPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	SetShowMouseCursor(true);

	// Axis
	InputComponent->BindAxis("MoveForward",		this, &ThisClass::OnInputAxis_MoveForward);
	InputComponent->BindAxis("MoveRight",		this, &ThisClass::OnInputAxis_MoveRight);

	InputComponent->BindAxis("Turn",			this, &ThisClass::OnInputAxis_Turn);
	InputComponent->BindAxis("TurnRate",		this, &ThisClass::OnInputAxis_TurnRate);
	InputComponent->BindAxis("LookUp",			this, &ThisClass::OnInputAxis_Lookup);
	InputComponent->BindAxis("LookUpRate",		this, &ThisClass::OnInputAxis_LookupRate);

	// Action
	InputComponent->BindAction("Crouch",		IE_Pressed,	this, &ThisClass::OnInputAction_Crouch_Pressed);
	InputComponent->BindAction("Equip",			IE_Pressed,	this, &ThisClass::OnInputAction_Equip_Pressed);
	InputComponent->BindAction("Fire",			IE_Pressed,	this, &ThisClass::OnInputAction_Fire_Pressed);
	InputComponent->BindAction("Jump",			IE_Pressed,	this, &ThisClass::OnInputAction_Jump_Pressed);
}

void AstcTestAnimPlayerController::OnInputAxis_MoveForward(float value) {
	InputDirection.X = value;
}

void AstcTestAnimPlayerController::OnInputAxis_MoveRight(float value) {
	InputDirection.Y = value;
}

void AstcTestAnimPlayerController::OnInputAxis_Turn(float value) {
	URS_LOG_INLINE("OnInputAxis_Turn: {}", value);
	AddYawInput(value);
}

void AstcTestAnimPlayerController::OnInputAxis_TurnRate(float value) {
	URS_LOG_INLINE("OnInputAxis_TurnRate: {}", value);
	AddYawInput(value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AstcTestAnimPlayerController::OnInputAxis_Lookup(float value) {
	URS_LOG_INLINE("OnInputAxis_Lookup: {}", value);
	AddPitchInput(value);
}

void AstcTestAnimPlayerController::OnInputAxis_LookupRate(float value) {
	URS_LOG_INLINE("OnInputAxis_LookupRate: {}", value);
	AddPitchInput(value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AstcTestAnimPlayerController::OnInputAction_Crouch_Pressed() {
	if (!MyCharacter) return;
	URS_LOG("Crouch");
	MyCharacter->MyCrouch = !MyCharacter->MyCrouch;
}

void AstcTestAnimPlayerController::OnInputAction_Equip_Pressed() {
	if (!MyCharacter) return;
	MyCharacter->MyEquip();
}

void AstcTestAnimPlayerController::OnInputAction_Fire_Pressed() {
	if (!MyCharacter) return;
	MyCharacter->MyFire();
}

void AstcTestAnimPlayerController::OnInputAction_Jump_Pressed() {
	if (!MyCharacter) return;
	MyCharacter->Jump();
}
