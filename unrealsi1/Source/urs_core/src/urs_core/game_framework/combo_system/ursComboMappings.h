#pragma once

#include "../../common/urs_core_common.h"

#include <InputAction.h>
#include <InputActionValue.h>

#include "ursComboMappings.generated.h"

class UInputAction;
class UursComboConfigs;

class AursCharacter;

DECLARE_DELEGATE_OneParam(FursFnComboExecute, const UursComboSet*);

UENUM()
enum class EursComboSystemState
{
	None = 0,
	Interrupt,
	Block,
	Commit,
	Reset,
	Complete,
	_Count,
};
// ENUM_CLASS_FLAGS(EComboSystemState)

USTRUCT()
struct UNREALSI1_API FursComboKey
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) TObjectPtr<const UInputAction>	inputAction = nullptr;
	UPROPERTY(EditAnywhere) FInputActionValue				value;

public:
	FursComboKey() {}
	FursComboKey(const UInputAction* ia, const FInputActionValue& iaValue) : inputAction(ia), value(iaValue) {}
};

UCLASS(BlueprintType)
class UNREALSI1_API UursComboSet : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) TArray<FursComboKey>				comboKeys;
	UPROPERTY(EditAnywhere) TArray<TObjectPtr<UAnimMontage> >	montages;
};

#if 0
#pragma mark --- UursComboConfigs-Decl ---
#endif // 0
#if 1

UCLASS(BlueprintType)
class UNREALSI1_API UursComboConfigs : public UDataAsset
{
	GENERATED_BODY()
public:
	template<class CHARACTER> void bindToMappings(FursComboMappings& mappings, CHARACTER* ch);
};

template<class CHARACTER> inline void UursComboConfigs::bindToMappings(FursComboMappings& mappings, CHARACTER* ch) {}

#endif

#if 0
#pragma mark --- UursComboMappings-Decl ---
#endif // 0
#if 1

USTRUCT()
struct UNREALSI1_API FursComboMappings /*: public ursNonCopyable*/
{
	GENERATED_BODY()
public:
	FursFnComboExecute* findComboCallback(const UursComboSet* set);
	const UursComboSet* findComboSet(const TArray<FursComboKey>& keys);

	void executeComboSet(const UursComboSet* set);

public:
	template<class COMBO_CONFIGS, class CHARACTER> void setComboConfigs(COMBO_CONFIGS* comboConfigs, CHARACTER* ch);
	template<class CHARACTER> void bindComboSet(const UursComboSet* set, CHARACTER* ch, void(CHARACTER::*Func)(const UursComboSet* set));

protected:
	UPROPERTY(VisibleAnywhere) TObjectPtr<const UursComboConfigs>		_comboConfigs;
	UPROPERTY(VisibleAnywhere) TArray<TObjectPtr<const UursComboSet> >	_comboSets;
	TMap<const UursComboSet*, FursFnComboExecute>						_comboCallbackTable;	// use TObjectPtr<const UursComboSet> if no TArray<TObjectPtr<const UursComboSet> >
};

template<class COMBO_CONFIGS, class CHARACTER> inline
void 
FursComboMappings::setComboConfigs(COMBO_CONFIGS* comboConfigs, CHARACTER* ch)
{
	static_assert(ursIsBaseOf<UursComboConfigs, COMBO_CONFIGS>, "invalid ComboConfigs type");
	static_assert(ursIsBaseOf<AursCharacter,	CHARACTER>,		"invalid AursCharacter type");

	check(comboConfigs && ch);
	comboConfigs->bindToMappings(*this, ch);
}

template<class CHARACTER> inline
void 
FursComboMappings::bindComboSet(const UursComboSet* set, CHARACTER* ch, void(CHARACTER::* func)(const UursComboSet* set))
{
	auto& fn = _comboCallbackTable.Add(set);
	fn.BindUObject(ch, func);

	_comboSets.Add(set);
}

#endif
