#include "trgActor.h"
#include "trgTestComputeShader.h"

#include <urs_core/common/ursLog.h>

AtrgActor::AtrgActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup a static mesh component for this actor
	ExampleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Example Mesh"));
	// Set the static mesh to the cube included with the engine
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	ExampleMesh->SetStaticMesh(CubeMesh.Object);
	// Make the static mesh component the root of this actor
	RootComponent = ExampleMesh;

	// Get a reference to the CustomeComputeModule
	//ComputeModule = FModuleManager::LoadModuleChecked<FCustomComputeModule>("CustomComputeModule");
}

void 
AtrgActor::BeginPlay()
{
	Super::BeginPlay();

	if (!RenderTarget)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No Render Target"));
		this->SetActorTickEnabled(false);
	}
	else if (!ExampleMesh)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No Static Mesh Property"));
		this->SetActorTickEnabled(false);
	}
}

void 
AtrgActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto vertices = getVertices(this);
	if (vertices.Num() > 0)
	{
		auto vertex = vertices[0];
		vertex.Normalize();

		URS_LOG_INLINE("urs_log: vertex: {}", vertex);
		//String str = FString::Printf(TEXT("- after normalize vertices[0]=[%f, %f, %f]"), vertex.X, vertex.Y, vertex.Z);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, str);
	}
	enqueueRenderCommand(RenderTarget, vertices);
}

void 
AtrgActor::enqueueRenderCommand(UTextureRenderTarget2D* texRdt, const TArray<FVector3f>& Vertices)
{
	TShaderMapRef<FtrgTestComputeShader> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	UTextureRenderTarget2D* RenderTargetParam = texRdt;
	TArray<FVector3f> VerticesParam = Vertices;

	ENQUEUE_RENDER_COMMAND(ComputeShader)(
		[
			ComputeShader,
			RenderTargetParam,
			VerticesParam
		](FRHICommandListImmediate& RHICmdList)
		{
			ComputeShader->BuildAndExecuteGraph(
				RHICmdList,
				RenderTargetParam,
				VerticesParam);
		});
}

TArray<FVector3f> 
AtrgActor::getVertices(AActor* Actor)
{
	// The array we'll return
	TArray<FVector3f> MeshVerts;

	// Get a static mesh from the first component
	TArray<UStaticMeshComponent*> StaticMeshComponents = TArray<UStaticMeshComponent*>();
	Actor->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
	UStaticMesh* StaticMesh = StaticMeshComponents[0]->GetStaticMesh();

	// Check if the static mesh is null
	if (!StaticMesh)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("StaticMesh[0] was null for actor: ")).Append(Actor->GetName()));
		return MeshVerts;
	}

	// Check if this static mesh has a LOD 
	if (!(StaticMesh->GetRenderData()->LODResources.Num() > 0))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Each mesh must have the supplied LOD To Use"));
		return MeshVerts;
	}

	// Get the vertices
	FPositionVertexBuffer* VertexBuffer = &StaticMesh->GetRenderData()->LODResources[0].VertexBuffers.PositionVertexBuffer;
	for (uint32 VertIdx = 0; VertIdx < VertexBuffer->GetNumVertices(); VertIdx++)
	{
		// Get this vertex
		FVector3f VertexLS = VertexBuffer->VertexPosition(VertIdx);
		
		// Transform from local to world space
		FVector VertexWS = Actor->GetTransform().TransformPosition(FVector{VertexLS});

		// Add it to the array we'll return
		MeshVerts.Add(FVector3f{VertexWS});	// NOTE: .Add can be pretty slow!
	}

	return MeshVerts;
}
