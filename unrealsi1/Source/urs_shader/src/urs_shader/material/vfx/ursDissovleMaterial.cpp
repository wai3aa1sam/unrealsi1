#include "ursDissovleMaterial.h"


#if 0
#pragma mark --- FursDissovleMaterial-Impl ---
#endif // 0
#if 1

void 
AursDissovleMaterial::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);

	auto* world = GetWorld();

	if (ursInputUtil::isKeyPressed(EKeys::R, world))
	{
		createDynamicMaterial();
		if (m_mtlInst)
		{
			static float dissolve = 0.0;
			dissolve += timeScale * DeltaSecond;
			m_mtlInst->SetScalarParameterValue(TEXT("dissolve"), dissolve);
			if (dissolve > 1.0f)
			{
				dissolve = 0;
			}
		}
	}

}

#endif

