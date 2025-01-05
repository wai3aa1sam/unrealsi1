#include "ursComboSystem.h"

#include <InputAction.h>
#include <urs_core/game_framework/ursPlayerController.h>

#include "../ursCharacter.h"

#if 0
#pragma mark --- UursComboSystem-Decl ---
#endif // 0
#if 1

/*
* montage priority? when character is getting hitted, but it still attacking
* 
*/

UursComboSystem::UursComboSystem()
{
	comboWindowDuration = 2.0;
}

void 
UursComboSystem::update(float dt, ACharacter* ch)
{
	// check within combo time
	// find the _comboMappings in _comboKeyBuffer
	// set character pending 

	/*
	* TODO:
	
	~ mappings.bindComboSet(csAttack, ch, &CHARACTER::combo_Attack);		// new separate function to check and bind
	// add a ComboState bidning, if xx state is triggered, then the bound fn will be called

	~ 3 state, Interrupt state -> Commit State -> Reset State

	*/

	/*
	* corresponding movement if no real combo
	*/
	URS_ASSERT(false, "UursComboSystem not yet support");

	if (_state == EursComboSystemState::Reset)
	{
		_fnComboReset.ExecuteIfBound();
		_state = EursComboSystemState::Interrupt;
	}

	const UursComboSet* fallbackCombo = nullptr;
	TArray<FursComboKey> curFrameBuf;
	{
		getCurrentFrameComboKeyBufferTo(&curFrameBuf);
		fallbackCombo = _comboMappings.findComboSet(curFrameBuf);
	}

	bool isNewComboStart = curFrameBuf.Num() > 0 && !comboWindowTimer.IsSet();
	if (isNewComboStart)
	{
		comboWindowTimer = 0.0f;
	}

	if (comboWindowTimer.IsSet())
	{
		auto curComboTime = comboWindowTimer.GetValue();
		comboWindowTimer = comboWindowTimer.GetValue() + dt;

		auto* pendingComboSet = _comboMappings.findComboSet(_comboKeyBuffer);

		// do not execute twice by _lastKeyBufferSize != _comboKeyBuffer.Num()
		if (pendingComboSet && _lastKeyBufferSize != _comboKeyBuffer.Num())
		{
			setPendingComboSet(pendingComboSet);
		}

		bool isOverTime = curComboTime >= comboWindowDuration;
		if (isOverTime)
		{
			comboWindowTimer.Reset();
			clear();
		}
	}

	if (_pendingComboSet /*&& _state != EursComboSystemState::Block*/)
	{
		_comboMappings.executeComboSet(_pendingComboSet);
		_pendingComboSet = nullptr;
	}
	else if (fallbackCombo /*&& _state != EursComboSystemState::Block*/)
	{
		_comboMappings.executeComboSet(fallbackCombo);
	}

	_lastKeyBufferSize = _comboKeyBuffer.Num();
	
	URS_DUMP_VAR_INLINE(_lastKeyBufferSize);
	{
		FString comboKeyBuffer;
		auto* PlayerController	= Cast<APlayerController>(ch->GetController());
		if (PlayerController)
		{
			auto* Subsystem	= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
			if (Subsystem)
			{
				for (auto& e : _comboKeyBuffer)
				{
					auto keys = Subsystem->QueryKeysMappedToAction(e.inputAction);

					FString temp;
					ursFormatTo(temp, ", {}", keys);
					comboKeyBuffer.Append(temp);
				}
				URS_DUMP_VAR_INLINE(comboKeyBuffer);
			}
		}
	}
}

void 
UursComboSystem::comboBegin()
{

}

void 
UursComboSystem::comboEnd()
{
	// broadcast combo_ResetState
	clear();
}

void 
UursComboSystem::clear()
{
	_comboKeyBuffer.Empty();
	setPendingComboSet(nullptr);
}

//void 
//UursComboSystem::comboUpdate(float dt)
//{
//	switch (state)
//	{
//		case EursComboSystemState::Interrupt:	{}	break;
//		case EursComboSystemState::Block:		{}	break;
//		case EursComboSystemState::Commit:		{}	break;
//		case EursComboSystemState::Complete:	{}	break;
//	}
//}

void 
UursComboSystem::commitCombo()
{
	auto* fn = _comboMappings.findComboCallback(_pendingComboSet);
	if (fn)
	{
		fn->ExecuteIfBound(_pendingComboSet);
	}
}

void
UursComboSystem::addComboKey(const FursComboKey& comboKey)
{
	_comboKeyBuffer.Add(comboKey);
}

void 
UursComboSystem::addComboKey(const UInputAction* ia, const FInputActionValue& iaValue)
{
	addComboKey(FursComboKey{ ia, iaValue });
}

void 
UursComboSystem::addComboKey(const FInputActionInstance& iaInst)
{
	addComboKey(FursComboKey{ iaInst.GetSourceAction(), iaInst.GetValue() });
}

void 
UursComboSystem::setPendingComboSet(const UursComboSet* comboSet)
{
	_pendingComboSet = comboSet;
}

void 
UursComboSystem::setComboSystemState(EursComboSystemState v)
{
	_state = v;
}

void 
UursComboSystem::getCurrentFrameComboKeyBufferTo(TArray<FursComboKey>* out)
{
	URS_ASSERT(out);

	out->Empty();

	auto n = _lastKeyBufferSize - _comboKeyBuffer.Num();
	out->Reserve(FMath::Max(0, n));
	for (int32 i = _lastKeyBufferSize; i < _comboKeyBuffer.Num(); ++i)
	{
		out->Add(_comboKeyBuffer[i]);
	}
}

#endif
