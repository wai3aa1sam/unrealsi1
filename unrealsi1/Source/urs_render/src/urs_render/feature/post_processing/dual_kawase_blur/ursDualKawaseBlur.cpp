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

	_dkBlurSVExt = FSceneViewExtensions::NewExtension<FursDualKawaseBlurSceneViewExt>(this);

	if (auto* world = GetWorld())
	{
		_demoActor = GetWorld()->SpawnActor<AursSimpleParticle>();
		_demoActor->SetActorTickEnabled(false);
	}
}

void 
AursDualKawaseBlur::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto& configs = _configs;

	if (isShowDemo && _demoActor)
	{
		#if 0
		if (_demoCurve)
		{
			//float demoCurveMinTime, demoCurveMaxTime;
			//_demoCurve->GetTimeRange(demoCurveMinTime, demoCurveMaxTime);
			//float demoCurveLength = demoCurveMaxTime - demoCurveMinTime;

			////float TimeNormalized = FMath::Clamp(_demoCurveTimer / demoCurveLength, 0.0f, 1.0f);
			//float demoCurveTime = demoCurveMinTime + FMath::Fmod(_demoCurveTimer, demoCurveLength);
			//_demoValue = _demoCurve->GetFloatValue(demoCurveTime);
		}
		#endif // 0
		configs.blurRadius = FMath::Clamp(configs.maxBlurRadius * ((FMath::Sin(demoTimer * demoBlurSpeed) + 1.0f) * 0.5f), 1, configs.maxBlurRadius);
		demoTimer += DeltaTime;
		
		_demoActor->Tick(DeltaTime);
	}

	if (configs.isExecuteBlur)
	{
		_dkBlurSVExt->requestExecute(configs);
	}
}

#endif
