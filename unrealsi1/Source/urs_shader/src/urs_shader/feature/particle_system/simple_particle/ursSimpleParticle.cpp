#include "ursSimpleParticle.h"

#include <GameFramework/GameUserSettings.h>

#include <ProceduralMeshComponent.h>
#include <Engine/StaticMesh.h>

// CoreMesh.h

#if 0
#pragma mark --- AursSimpleParticle-Impl ---
#endif // 0
#if 1

AursSimpleParticle::AursSimpleParticle()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = ursActorUtil::createDefault<USceneComponent>(this);

	URS_CDO_FINDER(_configs.texture, "/Script/Engine.Texture2D'/Engine/Tutorial/Mobile/TutorialAssets/android_Icon'");
}

void 
AursSimpleParticle::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);

	if (GEngine) 
	{
		/*
		* TODO: scoped set frame
		*/
		GEngine->bUseFixedFrameRate = false;
		GEngine->FixedFrameRate = 60.0f;
		GEngine->GameUserSettings->SetFrameRateLimit(60);
		
		//UGameUserSettings* gameUserSettings = UGameUserSettings::GetGameUserSettings();
		//if (gameUserSettings)
		//{
		//  gameUserSettings->SetFrameRateLimit(60.0f);
		//  gameUserSettings->ApplySettings(false);   // will save to GGameUserSettingsIni
		//}
		
	}

	_simpleParticleSvExt = FSceneViewExtensions::NewExtension<FursSimpleParticleSceneViewExt>(this);
	#if 0
	if (auto* world = GetWorld())
	{
		world->GetSubsystem<UursSimpleParticleSubSystem>()->setSimpleParticle(this);
	}
	#endif // 0
}

void 
AursSimpleParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto& configs = _configs;

	if (RootComponent)
	{
		configs.emitPosition = FVector3f(RootComponent->GetComponentLocation());
	}

	configs.deltaTime = DeltaTime * configs.timeScale;

	configs.emitPerSecondRemain += DeltaTime * configs.emitPerSecond;

	int newParticleCount = static_cast<int>(configs.emitPerSecondRemain);
	configs.emitPerSecondRemain -= newParticleCount;

	configs.newParticleStart	= configs.particleIndex;
	configs.newParticleEnd		= (configs.particleIndex + newParticleCount) % configs.maxParticleCount;

	configs.particleIndex += newParticleCount;
	configs.particleIndex %= configs.maxParticleCount;
	configs.activeParticleCount = FMath::Max(configs.particleIndex, configs.activeParticleCount);

	if (configs.isValid())
	{
		_simpleParticleSvExt->requestExecute(configs);
	}
}

#endif
