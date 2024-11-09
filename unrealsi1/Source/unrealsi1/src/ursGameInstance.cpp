#include "ursGameInstance.h"

void 
UursGameInstance::OnStart() 
{
	Super::OnStart();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, "ursGameInstance::OnStart()");

		#if URS_CORE
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, "URS_CORE");
		#endif
	}
}

