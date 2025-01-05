// Fill out your copyright notice in the Description page of Project Settings.


#include "stcTestActor.h"

// Sets default values
AstcTestActor::AstcTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent = Util::createDefault<UStaticMeshComponent>(this);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube'"));
	MeshComponent->SetStaticMesh(MeshObj.Object);

}

// Called when the game starts or when spawned
void AstcTestActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Hello World %d"), 200);

	demoStrFormat();
	demoEnum();
}

// Called every frame
void AstcTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Testing"));

	FRotator Rot = GetActorRotation();
	Rot.Yaw += RotateSpeed * DeltaTime;
	SetActorRotation(Rot);
}

void AstcTestActor::demoStrFormat()
{
	const char*    sz  = "Hello";
	const wchar_t* wcs = L"Hello";
	const TCHAR*   tcs = TEXT("Hello");

	{
		FString str = FString::Printf(TEXT("FString Printf %d %d %f %s"), 1, 2, 1.23f, TEXT("Hi!"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	{
		FString str = FString::Printf(TEXT("FString Printf is unsafe %s"), "Hi!");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	{
		FStringFormatOrderedArguments Args;
		Args.Add(123);
		Args.Add(2);
		Args.Add(1.23f);
		Args.Add(TEXT("Hi!"));
		FString str = FString::Format(TEXT("FString Format Ordered {0} {1} {2} {3}"), Args);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	{
		FStringFormatNamedArguments Args;
		Args.Add("A", 123);
		Args.Add("B", 2);
		Args.Add("C", 1.23f);
		Args.Add("D", TEXT("Hi!"));
		FString str = FString::Format(TEXT("FString Format Named {A} {B} {C} {D}"), Args);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	{
		FString str = ursFormat("MyFormat {} {}", 123, "string");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	URS_LOG("MY_LOG Test {}", 123);
}

void AstcTestActor::demoEnum()
{
	UEnum* EnumInfo = StaticEnum<EstcMyLesson002_MyEnumClass>();
	int N = EnumInfo->NumEnums();
	for (int i = 0; i < N; i++)
	{
		int64 value = EnumInfo->GetValueByIndex(i);
		FName name  = EnumInfo->GetNameByIndex(i);
		URS_LOG("EnumInfo {} {} {}", i, value, name);
	}

	{
		auto value = static_cast<EstcMyLesson002_MyEnumClass>(EnumInfo->GetValueByNameString("B"));
		URS_LOG("EnumInfo GetValueByNameString {}", value);
	}

	auto EnumBitwiseOr = EstcMyLesson002_MyEnumClass::A | EstcMyLesson002_MyEnumClass::B;
	URS_LOG("EnumInfo EnumBitwiseOr {}", EnumBitwiseOr);
}


