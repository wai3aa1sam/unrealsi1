#pragma once

#include "urs_shader/common/urs_shader_common.h"

#include "ursSimpleParticleSceneViewExt.h"

#include "ursSimpleParticle.generated.h"

class FursSimpleParticleParams;
class AursSimpleParticle;

USTRUCT()
struct URS_SHADER_API FursSimpleParticleConfigs
{
	GENERATED_BODY()
public:
	static constexpr int numThreads = 64;
	static constexpr int particleNoiseCount = 2048;

public:
	UPROPERTY(EditAnywhere) int maxParticleCount = 1000;

	UPROPERTY(EditAnywhere) float emitPerSecond = 100;
	UPROPERTY(EditAnywhere) float emitPerSecondRemain;
	UPROPERTY(EditAnywhere) float deltaTime;

	UPROPERTY(EditAnywhere) FVector3f initVelocity			= FVector3f(0, 10, 0);
	UPROPERTY(EditAnywhere) FVector3f initVelocityVariant	= FVector3f(1, 0.2f, 1);

	UPROPERTY(EditAnywhere) float initLifespan = 5;
	UPROPERTY(EditAnywhere) float initLifespanVariant = 2;

	UPROPERTY(EditAnywhere) float gravity = -9.8f;
	UPROPERTY(EditAnywhere) float timeScale = 1;
	UPROPERTY(EditAnywhere) float bounciness = 0.75f;

	UPROPERTY(EditAnywhere) int m_activeParticleCount	= 0;
	UPROPERTY(EditAnywhere) int m_particleIndex			= 0;

	UPROPERTY(VisibleAnywhere)	FVector3f	emitPosition;
	UPROPERTY(EditAnywhere)		FTransform  plane;
};

struct FursSimpleParticleParamsCache
{
	TRefCountPtr<FRDGPooledBuffer> particlePositionBuffer	= nullptr;
	TRefCountPtr<FRDGPooledBuffer> particleVelocityBuffer	= nullptr;
	TRefCountPtr<FRDGPooledBuffer> particleLifespanBuffer	= nullptr;
	TRefCountPtr<FRDGPooledBuffer> particleNoiseBuffer		= nullptr;
};

struct FursSimpleParticleRdgRscsRef
{
	FRDGBufferRef particlePositionBuffer	= nullptr;
	FRDGBufferRef particleVelocityBuffer	= nullptr;
	FRDGBufferRef particleLifespanBuffer	= nullptr;
	FRDGBufferRef particleNoiseBuffer		= nullptr;
};

#if 0
#pragma mark --- AursSimpleParticle-Decl ---
#endif // 0
#if 1

UCLASS()
class URS_SHADER_API AursSimpleParticle : public AActor
{
	GENERATED_BODY()
public:	
	// The mesh we'll get the data from
	UPROPERTY(VisibleAnywhere, Category = "urs") UStaticMeshComponent* ExampleMesh = nullptr;

	// The render-target we'll pass onto the GPU to be written to
	UPROPERTY(EditAnywhere, Category = "urs")	UTextureRenderTarget2D* RenderTarget = nullptr;

	UPROPERTY(EditAnywhere, Category = "urs")	FursSimpleParticleConfigs	_configs;

	UPROPERTY(EditAnywhere, Category = "urs")	TObjectPtr<UStaticMesh> _mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "urs")	bool tempIsQuadReverseDepth = false;

public:
	AursSimpleParticle();

public:
	void setupShaderParams(FursSimpleParticleParams& out, FursSimpleParticleParamsCache& outParamsCache, FursSimpleParticleRdgRscsRef& outRdgRscsRef, FRDGBuilder& rdgBuilder, const FursSimpleParticleConfigs& configs);
	void RenderThread_render(FRDGBuilder& rdgBuilder, const FSceneView& sceneView);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	struct PassParams
	{
		const FSceneView*				sceneView;
		FursSimpleParticleConfigs		configs;
		FursSimpleParticleRdgRscsRef	rdgRscsRef;
		
	};
	void addSimulateParticlePass(FRDGBuilder& rdgBuilder, PassParams* passParams);
	void addRenderParticlePass(FRDGBuilder& rdgBuilder, PassParams* passParams);

private:
	void createQuad(UStaticMesh* o);

private:
	//UPROPERTY(EditAnywhere, Category = "urs")	FursSimpleParticleResources _rscs;
	FursSimpleParticleParamsCache	_paramCache;
	PassParams _passParams;

	TSharedPtr<FursSimpleParticleSceneViewExt> _simpleParticleSvExt;
};

#endif