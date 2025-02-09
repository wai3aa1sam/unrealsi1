#pragma once

#include "urs_shader/common/urs_shader_common.h"

#include "trgActor.generated.h"

struct FursSimpleParticleParams;

USTRUCT()
struct FursSimpleParticleConfigs
{
	const int numThreads = 64;
	int MaxParticleCount = 100;

	float emitPerSecond = 1;
	float emitPerSecondRemain;

	FVector3f initVelocity = FVector3f(0, 10, 0);
	FVector3f initVelocityVariant = FVector3f(1, 0.2f, 1);

	float initLifespan = 5;
	float initLifespanVariant = 2;

	float gravity = -9.8f;
	float timeScale = 1;
	float bounciness = 0.75f;

	int m_activeParticleCount	= 0;
	int m_particleIndex			= 0;

	FPlane colliderPlane;
	FTransform colliderPlane2;
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

struct FursSimpleParticleParamCache
{
	const int particleNoiseCount = 2048;

	TRefCountPtr<FRDGPooledBuffer> particlePositionBuffer;
	TRefCountPtr<FRDGPooledBuffer> particleVelocityBuffer;
	TRefCountPtr<FRDGPooledBuffer> particleLifespanBuffer;
	TRefCountPtr<FRDGPooledBuffer> particleNoiseBuffer;
};

#if 0
#pragma mark --- AursSimpleParticle-Decl ---
#endif // 0
#if 1

UCLASS()
class AursSimpleParticle : public AActor
{
	GENERATED_BODY()
public:	
	// The mesh we'll get the data from
	UPROPERTY(VisibleAnywhere, Category = "urs") UStaticMeshComponent* ExampleMesh = nullptr;

	// The render-target we'll pass onto the GPU to be written to
	UPROPERTY(EditAnywhere, Category = "urs")	UTextureRenderTarget2D* RenderTarget = nullptr;

	UPROPERTY(EditAnywhere, Category = "urs")	FursSimpleParticleConfigs	configs;

private:
	//UPROPERTY(EditAnywhere, Category = "urs")	FursSimpleParticleResources _rscs;
	UPROPERTY(EditAnywhere, Category = "urs")	FursSimpleParticleParamCache _paramCache;
public:
	AursSimpleParticle();

public:
	void setupShaderParams(FursSimpleParticleParams& out, FursSimpleParticleParamCache& outParamCache, FRDGBuilder& rdgBuilder, const SimpleParticleConfigs& configs);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void enqueueRenderCommand(UTextureRenderTarget2D* texRdt, const TArray<FVector3f>& Vertices);
	//TArray<FVector3f> getVertices(AActor* Actor);
};

#endif