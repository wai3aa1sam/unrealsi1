#include "ursPlayerInput.h"

#if 0
#pragma mark --- UursPlayerInput-Impl ---
#endif // 0
#if 1

UursPlayerInput::UursPlayerInput()
{

}

UursPlayerInput::~UursPlayerInput()
{

}

void 
UursPlayerInput::getPressedKeyTo(TArray<FKey>* out, APlayerController* PlayerController)
{
    auto& o = *out;

	//APlayerController* PlayerController = GetOuterAPlayerController();
	ULocalPlayer* LocalPlayer = PlayerController ? Cast<ULocalPlayer>(PlayerController->Player) : nullptr;
	if (LocalPlayer != nullptr)
	{
		for (const auto& e : GetKeyStateMap())
		{
			const FKey&			key			= e.Key;
			const FKeyState&	keyState	= e.Value;
			/*if (KeyState.bDown)
			{
				o.Add(It.Key());
			}*/

			if (!key.IsAnalog() && keyState.EventCounts[IE_Pressed].Num() > 0)
			{
				o.Add(key);
			}
		}
	}
}

#endif