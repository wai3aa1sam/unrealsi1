#pragma once

#include "urs_render/common/urs_render_common.h"
#include "ursSimpleParticleSceneViewExt.h"
#include "ursSimpleParticle.h"

#include "ursSimpleParticleSubSystem.generated.h"

class AursSimpleParticle;

#if 0
#pragma mark --- UursSimpleParticleSubsystem-Decl ---
#endif // 0
#if 1

UCLASS()
class UursSimpleParticleSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void setSimpleParticle(AursSimpleParticle* simpleParticle) { _simpleParticle = simpleParticle; }

private:
	UPROPERTY(VisibleAnywhere) TWeakObjectPtr<AursSimpleParticle> _simpleParticle = nullptr;
	TSharedPtr<FursSimpleParticleSceneViewExt> _simpleParicleSvExt = nullptr;
};

#endif