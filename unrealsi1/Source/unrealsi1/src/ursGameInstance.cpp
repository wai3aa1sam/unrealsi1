#include "ursGameInstance.h"

void 
UursGameInstance::OnStart() 
{
	Super::OnStart();

	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, "ursGameInstance::OnStart()");
		URS_LOG("ursGameInstance::OnStart()");
	}
}

