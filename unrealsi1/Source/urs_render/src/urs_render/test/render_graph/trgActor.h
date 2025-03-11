#pragma once

/*
reference:
~ https://github.com/nfgrep/CustomComputeExample
*/

#include "urs_render/common/urs_render_common.h"

#include "trgActor.generated.h"


#if 0
#pragma mark --- AtadCharacter-Decl ---
#endif // 0
#if 1

UCLASS()
class AtrgActor : public AActor
{
	GENERATED_BODY()
public:	
	// The mesh we'll get the data from
	UPROPERTY(VisibleAnywhere, Category = "urs") UStaticMeshComponent* ExampleMesh = nullptr;

	// The render-target we'll pass onto the GPU to be written to
	UPROPERTY(EditAnywhere, Category = "urs")	UTextureRenderTarget2D* RenderTarget = nullptr;

public:	
	AtrgActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void enqueueRenderCommand(UTextureRenderTarget2D* texRdt, const TArray<FVector3f>& Vertices);
	TArray<FVector3f> getVertices(AActor* Actor);
};

#endif