// Fill out your copyright notice in the Description page of Project Settings.


#include "urs_tutorial/SimpleTalkCpp/Basic/stcTestComponentActor.h"
#include "Components/BillboardComponent.h"

#if 0
#pragma mark --- UstcCCube-Impl ---
#endif // 0
#if 1

UstcCCube::UstcCCube()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshObj(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube'"));
	SetStaticMesh(meshObj.Object);
}

#endif

#if 0
#pragma mark --- UstcCRotate-Impl ---
#endif // 0
#if 1



UstcCRotate::UstcCRotate()
{
	PrimaryComponentTick.bCanEverTick = true;
	//	PrimaryComponentTick.bTickEvenWhenPaused = true;
	//	PrimaryComponentTick.TickGroup = TG_PrePhysics;
}

void UstcCRotate::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//	MY_LOG("UMyLesson003_RotateComponent Tick");

	auto* Actor = GetOwner();
	auto Rot = Actor->GetActorRotation();
	Rot.Yaw += rotateSpeed * DeltaTime;
	Actor->SetActorRotation(Rot);
}


#endif


#if 0
#pragma mark --- AstcBullet-Impl ---
#endif // 0
#if 1

AstcBullet::AstcBullet() {
	PrimaryActorTick.bCanEverTick = true;

	cCube = Util::createDefault<UstcCCube>(this, "Cube");
	RootComponent = cCube;
	cCube->SetRelativeScale3D(FVector(0.5f, 0.25f, 0.25f));
}

void AstcBullet::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	auto Loc = GetActorLocation();
	Loc += GetActorForwardVector() * (moveSpeed * DeltaSeconds);
	SetActorLocation(Loc);
}


#endif

#if 0
#pragma mark --- UstcCGun-Impl ---
#endif // 0
#if 1

UstcCGun::UstcCGun()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.5f;

	SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
}

void UstcCGun::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//	URS_LOG("Gun Tick");

	AActor* Actor = GetOwner();
	auto Loc = Actor->GetActorLocation();
	auto Rot = Actor->GetActorRotation();

	UClass* Cls = nullptr;
	// Cls = AstcBullet::StaticClass();

	if (auto* testCActor = Cast<AstcTestComponentActor>(Actor)) 
	{
		Cls = testCActor->bulletClass.Get();
	}

	if (Cls) 
	{
		AActor* bullet = GetWorld()->SpawnActor(Cls, &Loc, &Rot);

		#if WITH_EDITOR
		static FName folderPath(TEXT("_MyBullet"));
		bullet->SetFolderPath(folderPath);
		#endif
	}
}

#endif


// Sets default values
AstcTestComponentActor::AstcTestComponentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cBillboard = Util::createDefault<UBillboardComponent>(this);
	RootComponent = cBillboard;

	cRotate = Util::createDefault<UstcCRotate>(this, "Rotate");
}

// Called when the game starts or when spawned
void AstcTestComponentActor::BeginPlay()
{
	Super::BeginPlay();
	
	cGun = Util::newAttachComponent<UstcCGun>(this, RootComponent);
}

// Called every frame
void AstcTestComponentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

