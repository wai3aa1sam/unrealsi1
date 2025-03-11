#include "ursMaterialTestActor.h"


#if 0
#pragma mark --- AursMaterialTestActor-Impl ---
#endif // 0
#if 1

AursMaterialTestActor::AursMaterialTestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = ursActorUtil::createDefault<USceneComponent>(this);
	m_meshComp = ursActorUtil::newAttachComponent_Ctor<UStaticMeshComponent>(this, nullptr);
	RootComponent = m_meshComp;

	static UStaticMesh* mesh = nullptr;
	URS_CDO_FINDER(mesh, "/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube'");

	m_meshComp->SetStaticMesh(mesh);
}

void
AursMaterialTestActor::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	createDynamicMaterial();
}

void 
AursMaterialTestActor::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);


}

bool 
AursMaterialTestActor::ShouldTickIfViewportsOnly() const
{
	return true;
}

void 
AursMaterialTestActor::createDynamicMaterial()
{
	if (m_parentMaterial)
	{
		if (!m_mtlInst)
		{
			m_mtlInst = UMaterialInstanceDynamic::Create(m_parentMaterial, this);
		}
		if (m_mtlInst)
		{
			//m_mtlInst->SetScalarParameterValue(TEXT("Opacity"), 0.5f);
			//m_mtlInst->SetVectorParameterValue(TEXT("Color"), FLinearColor(0.0f, 0.0f, 1.0f, 1.0f));
			if (m_meshComp)
			{
				m_meshComp->SetMaterial(0, m_mtlInst);
			}
		}
	}
}

#endif

