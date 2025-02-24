#pragma once

#include "ursSimpleParticle_Common.h"
#include "ursSimpleParticleSceneViewExt.h"

#include "ursSimpleParticle.generated.h"

class FursSimpleParticleParams;
class AursSimpleParticle;

#if 0
#pragma mark --- AursSimpleParticle-Decl ---
#endif // 0
#if 1

UCLASS()
class URS_SHADER_API AursSimpleParticle : public AActor
{
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere, Category = "urs")	FursSimpleParticleConfigs	_configs;

public:
	AursSimpleParticle();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	TSharedPtr<FursSimpleParticleSceneViewExt> _simpleParticleSvExt;
};

#endif