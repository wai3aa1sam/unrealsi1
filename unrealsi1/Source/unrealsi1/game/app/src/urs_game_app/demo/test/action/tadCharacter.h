#pragma once

#include "urs_game_app/common/urs_game_app_common.h"

#include <urs_core/game_framework/ursCharacter.h>
#include <urs_core/game_framework/combo_system/ursComboSystem.h>

#include "tadPawnAction.h"

#include "tadCharacter.generated.h"

class UtadInputActionConfigs;
class UtadComboConfigs;

class UInputMappingContext;
class UInputAction;

class USpringArmComponent;
class UCameraComponent;

#if 0
#pragma mark --- AtadCharacter-Decl ---
#endif // 0
#if 1

UCLASS()
class UNREALSI1_API AtadCharacter : public AursCharacter 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "urs") TObjectPtr<UtadInputActionConfigs>	inputActionConfigs	= nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "urs") TObjectPtr<UtadComboConfigs>		comboConfigs		= nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "urs") TObjectPtr<UtadPawnActionConfigs>	pawnActionConfigs	= nullptr;

public:
	AtadCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION() void combo_Attack(const UursComboSet* comboSet);

	void resetCombo();
	void resetActionState();

	void doJump();
	void doStopJump();
	void doAttack();
	void doNextAttack();

public:
	void playMontage(UAnimMontage* animMtg);

public:
	UursComboSystem&		comboSystem();
	FtadPawnActionState&	pawnActionState();

private:
	const USkeletalMeshSocket* MyFindSocket(FName name);

	void _doAttack();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "urs") 
	TObjectPtr<USpringArmComponent>	_cameraBoom		= nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "urs")
	TObjectPtr<UCameraComponent>	_followCamera	= nullptr;

	TWeakObjectPtr<const USkeletalMeshSocket> _spawnBulletSocket;
	TWeakObjectPtr<const USkeletalMeshSocket> _aimStartSocket;

private:
	UPROPERTY(EditAnywhere, Category = "urs") TObjectPtr<UInputMappingContext>	_inputMapCtx	= nullptr;
	UPROPERTY(EditAnywhere, Category = "urs") TObjectPtr<UursComboSystem>		_comboSys		= nullptr;
	UPROPERTY(EditAnywhere, Category = "urs") FtadPawnActionState				_paState;
};

inline UursComboSystem&			AtadCharacter::comboSystem()		{ return *_comboSys; }
inline FtadPawnActionState&		AtadCharacter::pawnActionState()	{ return _paState; }

#endif

#if 0
#pragma mark --- UtadInputActionConfigs-Decl ---
#endif // 0
#if 1

/*
references:
~ https://github.com/ibbles/LearningUnrealEngine/blob/master/Creating%20new%20asset%20types.md
*/

UCLASS(BlueprintType)
class UNREALSI1_API UursInputActionConfigs : public UDataAsset
{
	GENERATED_BODY()
public:
};

UCLASS(BlueprintType)
class UNREALSI1_API UtadInputActionConfigs : public UursInputActionConfigs
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UInputAction> iaMove;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UInputAction> iaLook;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UInputAction> iaJump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UInputAction> iaCrouch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<UInputAction> iaAttack;
};

#endif

#if 0
#pragma mark --- UtadComboConfigs-Decl ---
#endif // 0
#if 1

UCLASS(BlueprintType)
class UNREALSI1_API UtadComboConfigs : public UursComboConfigs
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) TObjectPtr<const UursComboSet> csAttack;

public:
	template<class CHARACTER> void bindToMappings(FursComboMappings& mappings, CHARACTER* ch);
};

template<class CHARACTER> inline
void 
UtadComboConfigs::bindToMappings(FursComboMappings& mappings, CHARACTER* ch)
{
	Super::bindToMappings(mappings, ch);
	mappings.bindComboSet(csAttack, ch, &CHARACTER::combo_Attack);		// new separate function to check and bind
	// add a ComboState bidning, if xx state is triggered, then the binded fn will be called
}

#endif