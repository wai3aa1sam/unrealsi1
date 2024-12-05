#include "stcTestPlayerController.h"


#include <Kismet/GameplayStatics.h>
#include <GameFramework/GameModeBase.h>

AstcTestPlayerController::AstcTestPlayerController() 
{
	InputDirection = FVector::ZeroVector;
}

void AstcTestPlayerController::BeginPlay() {
	#if WITH_EDITOR
	static FName folderPath(TEXT("MyGame"));

	SetActorLabel(TEXT("MyController Test"));

	SetFolderPath(folderPath);
	if (auto* p = GetWorld()->GetAuthGameMode()) {
		p->SetFolderPath(folderPath);
	}
	#endif

	UpdateCameraTarget();
}

void AstcTestPlayerController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	//	auto* Game = GetWorld()->GetGameInstanceChecked<UMyLesson004_GameInstance>();

	URS_LOG_INLINE("InputDirection {}", InputDirection);
	/*if (GEngine) {
		FString msg = ursFormat("InputDirection {}", InputDirection);
		GEngine->AddOnScreenDebugMessage(1, 2, FColor::Purple, msg);
	}*/

	if (auto* p = GetPawn())
	{
		// p->AddMovementInput(InputDirection, 1);
		auto Loc = p->GetActorLocation();
		Loc += InputDirection * 100 * DeltaSeconds;
		p->SetActorLocation(Loc);
	}
}

void AstcTestPlayerController::SetupInputComponent() 
{
	Super::SetupInputComponent();

	SetShowMouseCursor(true);

	// Axis
	InputComponent->BindAxis("MoveForward",		this, &ThisClass::OnInputAxis_MoveForward);
	InputComponent->BindAxis("MoveRight",		this, &ThisClass::OnInputAxis_MoveRight);

	// Action
	InputComponent->BindAction("Jump",				IE_Pressed,		this, &ThisClass::OnInputAction_Jump_Pressed);
	InputComponent->BindAction("Jump",				IE_Released,	this, &ThisClass::OnInputAction_Jump_Released);
	InputComponent->BindAction("Jump",				IE_Axis,		this, &ThisClass::OnInputAction_Jump_Axis);
	InputComponent->BindAction("Jump",				IE_Repeat,		this, &ThisClass::OnInputAction_Jump_Repeat);
	InputComponent->BindAction("Jump",				IE_DoubleClick, this, &ThisClass::OnInputAction_Jump_DoubleClick);

	InputComponent->BindAction("MyChangeCamera",	IE_Pressed,		this, &ThisClass::OnInputAction_MyChangeCamera);
}

void AstcTestPlayerController::OnInputAxis_MoveForward(float value) { InputDirection.X = value; }
void AstcTestPlayerController::OnInputAxis_MoveRight  (float value) { InputDirection.Y = value; }

void AstcTestPlayerController::OnInputAction_Jump_Pressed()			{ URS_LOG("Jump_Pressed"); }
void AstcTestPlayerController::OnInputAction_Jump_Released()		{ URS_LOG("Jump_Released"); }
void AstcTestPlayerController::OnInputAction_Jump_Axis()			{ URS_LOG("Jump_Axis"); }
void AstcTestPlayerController::OnInputAction_Jump_Repeat()			{ URS_LOG("Jump_Repeat"); }
void AstcTestPlayerController::OnInputAction_Jump_DoubleClick()		{ URS_LOG("Jump_DoubleClick"); }

void AstcTestPlayerController::OnInputAction_MyChangeCamera() 
{
	URS_LOG("MyChangeCamera");
	CurrentCameraIndex++;

	UpdateCameraTarget();
}

void AstcTestPlayerController::UpdateCameraTarget() 
{
	static FName MyCameraTag(TEXT("MyCamera"));

	TArray<AActor*> CameraList;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), MyCameraTag, CameraList);

	int N = CameraList.Num();
	if (N <= 0) return;

	auto* Cam = CameraList[CurrentCameraIndex % N];
	SetViewTargetWithBlend(Cam);
}
