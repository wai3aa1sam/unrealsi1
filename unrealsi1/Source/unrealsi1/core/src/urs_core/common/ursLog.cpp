#include "ursLog.h"

DECLARE_LOG_CATEGORY_EXTERN(ursLog, Log, All);
DEFINE_LOG_CATEGORY(ursLog)

void ursLogger::output(int32 key, float timeToDisplay, const FString& msg) 
{
	if (GEngine) 
	{
		GEngine->AddOnScreenDebugMessage(key, timeToDisplay, FColor::Red, msg);
	}
	UE_LOG(ursLog, Warning, TEXT("%s"), *msg);
}