#pragma once

#include "../../common/urs_core_common.h"
#include "ursComboMappings.h"

#include "ursComboSystem.generated.h"

class AursCharacter;

DECLARE_DELEGATE(FursFnComboReset);

#if 0
#pragma mark --- UComboSystem-Decl ---
#endif // 0
#if 1

UCLASS()
class UNREALSI1_API UursComboSystem : public UObject
{
	GENERATED_BODY()
public:
	TOptional<float> comboWindowTimer	= 0.0;
	UPROPERTY(VisibleAnywhere) float			comboWindowDuration	= 0.1;

public:
	UursComboSystem();

public:
	void update(float dt, ACharacter* ch);

	void comboBegin();
	void comboEnd();
	//void comboUpdate(float dt);

	void commitCombo();

	void clear();

public:
	template<class COMBO_CONFIGS, class CHARACTER>void setComboConfigs(COMBO_CONFIGS* comboConfigs, CHARACTER* ch, void(CHARACTER::* fnResetCombo)());
	//void resetMappings(FursComboMappings& mappings, AursCharacter* ch);

	void addComboKey(const FursComboKey& comboKey);
	void addComboKey(const UInputAction* ia, const FInputActionValue& iaValue);
	void addComboKey(const FInputActionInstance& iaInst);
	void setPendingComboSet(const UursComboSet* comboSet);

	void setComboSystemState(EursComboSystemState v);

public:
	EursComboSystemState getComboState() const;

private:
	void getCurrentFrameComboKeyBufferTo(TArray<FursComboKey>* out);

private:
	UPROPERTY(VisibleAnywhere) int32				_lastKeyBufferSize = 0;
	UPROPERTY(VisibleAnywhere) TArray<FursComboKey>	_comboKeyBuffer;
	UPROPERTY(VisibleAnywhere) FursComboMappings	_comboMappings;

	UPROPERTY(VisibleAnywhere) EursComboSystemState	_state = EursComboSystemState::None;

	const UursComboSet* _pendingComboSet = nullptr;

	FursFnComboReset _fnComboReset;
};

template<class COMBO_CONFIGS, class CHARACTER> inline
void 
UursComboSystem::setComboConfigs(COMBO_CONFIGS* comboConfigs, CHARACTER* ch, void(CHARACTER::* fnResetCombo)())
{
	_comboMappings.setComboConfigs(comboConfigs, ch);
	_fnComboReset.BindUObject(ch, fnResetCombo);
}

inline EursComboSystemState UursComboSystem::getComboState() const { return _state; }

#endif
