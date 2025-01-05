// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "urs_tutorial/common/urs_tutorial_common.h"

#include "stcTestComponentActor.generated.h"

class UBillboardComponent;
class UstcCCube;

#if 0
#pragma mark --- UstcCCube-Decl ---
#endif // 0
#if 1
UCLASS(meta=(BlueprintSpawnableComponent))
class UNREALSI1_API UstcCCube : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UstcCCube();
};

#endif // 1

#if 0
#pragma mark --- UstcCRotate-Decl ---
#endif // 0
#if 1

UCLASS(ClassGroup=stc, meta=(BlueprintSpawnableComponent))
class UstcCRotate : public UActorComponent 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) float rotateSpeed = 100;

	UstcCRotate();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};

#endif

#if 0
#pragma mark --- AstcBullet-Decl ---
#endif // 0
#if 1

UCLASS()
class AstcBullet : public AursActor {
	GENERATED_BODY()
public:
	AstcBullet();

	UPROPERTY(VisibleAnywhere)	UstcCCube* cCube = nullptr;
	UPROPERTY(EditAnywhere)		float moveSpeed = 100;

	virtual void Tick(float DeltaSeconds) override;
};

#endif

#if 0
#pragma mark --- UstcCGun-Decl ---
#endif // 0
#if 1

UCLASS()
class UstcCGun : public UstcCCube {
	GENERATED_BODY()
public:
	// UPROPERTY(EditAnywhere) TSubclassOf<AstcBullet> bulletClass;

public:
	UstcCGun();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};


#endif

UCLASS()
class UNREALSI1_API AstcTestComponentActor : public AursActor
{
	GENERATED_BODY()
public:	
	UPROPERTY(VisibleAnywhere) UBillboardComponent* cBillboard	= nullptr;
	UPROPERTY(VisibleAnywhere) UstcCGun*			cGun		= nullptr;
	UPROPERTY(VisibleAnywhere) UstcCRotate*			cRotate		= nullptr;

	UPROPERTY(EditAnywhere) TSubclassOf<AstcBullet>	bulletClass;


public:	
	// Sets default values for this actor's properties
	AstcTestComponentActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
