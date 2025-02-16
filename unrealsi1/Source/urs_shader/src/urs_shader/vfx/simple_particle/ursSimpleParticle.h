#pragma once

#include "urs_shader/common/urs_shader_common.h"

#include "ursSimpleParticle.generated.h"

class FursSimpleParticleParams;

USTRUCT()
struct URS_SHADER_API FursSimpleParticleConfigs
{
	GENERATED_BODY()
public:
	static constexpr int numThreads = 64;
	int MaxParticleCount = 100;

	float emitPerSecond = 1;
	float emitPerSecondRemain;
	float deltaTime;

	FVector3f initVelocity = FVector3f(0, 10, 0);
	FVector3f initVelocityVariant = FVector3f(1, 0.2f, 1);

	float initLifespan = 5;
	float initLifespanVariant = 2;

	float gravity = -9.8f;
	float timeScale = 1;
	float bounciness = 0.75f;

	int m_activeParticleCount	= 0;
	int m_particleIndex			= 0;

	FVector3f	emitPosition;
	FTransform  plane;
};

//USTRUCT()
//struct FursSimpleParticleResources
//{
//	TArray<FVector3f>	particlePositions;
//	TArray<FVector3f>	particleVelocities;
//	TArray<FVector2f>	particleLifespans;		// x: remain, y: total
//	TArray<FVector3f>	particleNoises;
//	const int			particleNoiseCount = 2048;
//};

struct FursSimpleParticleParamsCache
{
	const int particleNoiseCount = 2048;

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

	UPROPERTY(EditAnywhere, Category = "urs")	TObjectPtr<UStaticMesh> mesh = nullptr;

public:
	AursSimpleParticle();

public:
	void setupShaderParams(FursSimpleParticleParams& out, FursSimpleParticleParamsCache& outParamsCache, FursSimpleParticleRdgRscsRef& outRdgRscsRef, FRDGBuilder& rdgBuilder, const FursSimpleParticleConfigs& configs);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void enqueueRenderCommand();
	void addSimulateParticlePass(FRDGBuilder& rdgBuilder, FursSimpleParticleRdgRscsRef& outRdgRscsRef, const FursSimpleParticleConfigs& configs);
	void addRenderParticlePass(FRDGBuilder& rdgBuilder, FursSimpleParticleRdgRscsRef& rdgRscsRef);

private:
	void createQuad(UStaticMesh* o);

private:
	//UPROPERTY(EditAnywhere, Category = "urs")	FursSimpleParticleResources _rscs;
	FursSimpleParticleParamsCache	_paramCache;
};

#endif