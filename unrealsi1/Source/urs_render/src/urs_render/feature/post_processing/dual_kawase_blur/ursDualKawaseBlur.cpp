#include "ursDualKawaseBlur.h"

#include <GameFramework/GameUserSettings.h>

#include "urs_render/feature/particle_system/simple_particle/ursSimpleParticle.h"

#if 0
#pragma mark --- AursDualKawaseBlur-Impl ---
#endif // 0
#if 1

AursDualKawaseBlur::AursDualKawaseBlur()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = ursActorUtil::createDefault<USceneComponent>(this);
}

void 
AursDualKawaseBlur::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine) 
	{
		GEngine->bUseFixedFrameRate = false;
		GEngine->FixedFrameRate = 60.0f;
		GEngine->GameUserSettings->SetFrameRateLimit(60);
	}

	if (auto* world = GetWorld())
	{
		auto& configs = _configs;
		configs.demoActor = GetWorld()->SpawnActor<AursSimpleParticle>();
		configs.demoActor->SetActorTickEnabled(false);
	}

	_dkBlurSVExt = FSceneViewExtensions::NewExtension<FursDualKawaseBlurSceneViewExt>(this);
}

void 
AursDualKawaseBlur::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto& configs = _configs;
	configs.tick(DeltaTime, *_dkBlurSVExt);
}

#endif
