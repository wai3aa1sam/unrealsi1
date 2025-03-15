#pragma once

#include "ursDualKawaseBlur_Common.h"
#include "ursDualKawaseBlurSceneViewExt.h"

#include "ursDualKawaseBlur.generated.h"

class FursDualKawaseBlurParams;
class AursDualKawaseBlur;

class AursSimpleParticle;

#if 0
#pragma mark --- AursDualKawaseBlur-Decl ---
#endif // 0
#if 1

UCLASS()
class URS_RENDER_API AursDualKawaseBlur : public AursActor		// TODO: AursRenderFeature
{
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere, Category = "urs")	FursDualKawaseBlurConfigs				_configs;
	UPROPERTY(EditAnywhere, Category = "urs")	TObjectPtr<UTextureRenderTarget2D>		renderTarget	= nullptr;
	//UPROPERTY(EditAnywhere, Category = "urs")	TObjectPtr<UCurveFloat>					demoAnimCurve	= nullptr;


public:
	AursDualKawaseBlur();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	TSharedPtr<FursDualKawaseBlurSceneViewExt> _dkBlurSVExt;
};

#endif