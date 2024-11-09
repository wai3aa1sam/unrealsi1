#pragma once

#include "GameFramework/PlayerController.h"

#include "GameFramework/GameModeBase.h"

#include "stcTestAnimPlayerController.generated.h"

UCLASS()
class AstcTestAnimGameMode : public AGameModeBase 
{
	GENERATED_BODY()
public:
	AstcTestAnimGameMode();
};

UCLASS()
class AstcTestAnimPlayerController : public APlayerController 
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Transient)
	FVector InputDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	virtual void SetupInputComponent() override;

	void OnInputAxis_MoveForward(float value);
	void OnInputAxis_MoveRight	(float value);

	void OnInputAxis_Turn		(float value);
	void OnInputAxis_TurnRate	(float value);
	void OnInputAxis_Lookup		(float value);
	void OnInputAxis_LookupRate	(float value);

	void OnInputAction_Crouch_Pressed();
	void OnInputAction_Equip_Pressed();
	void OnInputAction_Fire_Pressed();
	void OnInputAction_Jump_Pressed();


	UPROPERTY(VisibleAnywhere)
	class AstcTestAnimCharacter*	MyCharacter = nullptr;
};