#pragma once

#include "urs_shader/common/urs_shader_common.h"

#include <urs_core/game_framework/utility/ursInputUtil.h>

#include "ursMaterialTestActor.generated.h"

#if 0
#pragma mark --- AursMaterialTestActor-Decl ---
#endif // 0
#if 1

UCLASS()
class URS_SHADER_API AursMaterialTestActor : public AursActor
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Category = "urs") float timeScale = 1.0f;
    UPROPERTY(EditAnywhere, Category = "urs") uint8 isTriggered : 1;

public:
    AursMaterialTestActor();

public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSecond) override;

public:
    // WITH_EDITOR
    virtual bool ShouldTickIfViewportsOnly() const override;

public:
    void createDynamicMaterial();

protected:
    UPROPERTY(EditAnywhere, Category = "urs")    TObjectPtr<UMaterial>                   m_parentMaterial    = nullptr;
    UPROPERTY(EditAnywhere, Category = "urs")    TObjectPtr<UMaterialInstanceDynamic>    m_mtlInst           = nullptr;
    UPROPERTY(EditAnywhere, Category = "urs")    TObjectPtr<UStaticMeshComponent>        m_meshComp          = nullptr;
};


#endif