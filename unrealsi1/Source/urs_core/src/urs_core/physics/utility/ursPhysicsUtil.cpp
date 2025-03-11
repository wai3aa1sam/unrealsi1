#include "ursPhysicsUtil.h"

#include "urs_core/transform/utility/ursTransformUtil.h"

#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

#if 0
#pragma mark --- ursPhysicsUtil-Impl ---
#endif // 0
#if 1

bool 
ursPhysicsUtil::lineTraceByMousePos(FHitResult& outHit, UWorld* world, int32 playerIndex)
{
	check(world);
	//auto* world = GetWorld();

	auto* playerCtrl = UGameplayStatics::GetPlayerController(world, playerIndex);
	if (!playerCtrl) 
		return false;

	FVector worldPos, worldDir;
	playerCtrl->DeprojectMousePositionToWorld(worldPos, worldDir);

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

	FHitResult& hit = outHit;
	UKismetSystemLibrary::LineTraceSingleForObjects(world, worldPos, worldPos + worldDir * 9999.0f, objectTypes, true, {}, EDrawDebugTrace::None, hit, true);

	//hit.GetComponent();
	return true;
}

bool 
ursPhysicsUtil::lineTraceByMousePos_Editor(FHitResult& outHit, UWorld* world)
{
	check(world);

	FVector worldPos, worldDir;
	bool isSuccess = ursTransformUtil::deprojectMousePosToWorld_EditorViewport(worldPos, worldDir);
	if (!isSuccess)
		return false;

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

	FHitResult& hit = outHit;
	UKismetSystemLibrary::LineTraceSingleForObjects(world, worldPos, worldPos + worldDir * 9999.0f, objectTypes, true, {}, EDrawDebugTrace::None, hit, true);

	return true;

}
#endif

