#pragma once

#include "urs_tutorial/common/urs_tutorial_common.h"

#include <GameFramework/Character.h>

//#include "MyLesson006_Bullet.h"
#include "stcTestAnimCharacter.generated.h"

class AstcTestAnimBullet;

UCLASS()
class AstcTestAnimBullet : public AActor {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float SimPhysicTime;

	UPROPERTY(EditAnywhere)
	float Lifespan;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent = nullptr;


	virtual void Tick(float DeltaSeconds) override;

	AstcTestAnimBullet();

private:
	UPROPERTY(VisibleAnywhere, Transient)
	float	_lifeTime = 0;
};

UCLASS()
class AstcTestAnimCharacter : public ACharacter 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) bool MyCrouch = false;

	UPROPERTY(EditAnywhere) TSubclassOf<AstcTestAnimBullet> BulletClass;
	UPROPERTY(EditAnywhere) TWeakObjectPtr<AActor>			Target;

	UPROPERTY(EditAnywhere) UAnimMontage* Montage_Equip			= nullptr;
	UPROPERTY(EditAnywhere) UAnimMontage* Montage_Fire_Upper	= nullptr;

	UPROPERTY(EditAnywhere, Transient) float BlockMoveCurveValue = 0;

public:
	AstcTestAnimCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void MyEquip();

	void MyFire();
	void AnimNotify_Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) class USpringArmComponent*	CameraBoom		= nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) class UCameraComponent*		FollowCamera	= nullptr;

	const USkeletalMeshSocket* MyFindSocket(FName name);

	TWeakObjectPtr<USkeletalMeshSocket const> SpawnBulletSocket;
	TWeakObjectPtr<USkeletalMeshSocket const> AimStartSocket;
};