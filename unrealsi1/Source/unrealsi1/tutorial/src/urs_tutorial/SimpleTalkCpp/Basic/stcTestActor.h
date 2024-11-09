// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "urs_tutorial/common/urs_tutorial_common.h"

#include "stcTestActor.generated.h"

USTRUCT()
struct FstcMyLesson002_MyStruct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) float x;
};

// no reflection
USTRUCT(NoExport)
struct FstcMyLesson002_MyStruct2 {
	UPROPERTY(EditAnywhere) float x;
};

UCLASS()
class UstcMyLesson002_MyObject : public UObject {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) float x;
};

UENUM()
enum class EstcMyLesson002_MyEnumClass {
	A,
	B,
	C UMETA(DisplayName="CCCC"),
};
ENUM_CLASS_FLAGS(EstcMyLesson002_MyEnumClass)

UCLASS()
class UNREALSI1_API AstcTestActor : public AursActor
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere) int		TestInt		= 100;
	UPROPERTY(EditAnywhere) float	RotateSpeed = 360;

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditAnywhere)				int Test_Edit		= 0;
	UPROPERTY(VisibleAnywhere)			int Test_Visible	= 0;
	UPROPERTY(EditAnywhere, Transient)	int Test_Transient	= 0;

	UPROPERTY(EditAnywhere, Category="My Category")						int Test_Category		= 0;
	UPROPERTY(EditAnywhere, meta=(DisplayName = "Test Name"))			int Test_DisplayName	= 0;
	UPROPERTY(EditAnywhere, meta=(ClampMin = "0", ClampMax = "100"))	int Test_Clamp			= 0;

	UPROPERTY(EditAnywhere) bool Test_Condition_Bool = false;
	UPROPERTY(EditAnywhere, meta=(EditCondition="Test_Condition_Bool")) int Test_Condition_Int = 0;

	UPROPERTY(EditAnywhere) FString Test_FString;
	UPROPERTY(EditAnywhere) FName	Test_FName;
	UPROPERTY(EditAnywhere) FText	Test_FText;

	UPROPERTY(EditAnywhere) FstcMyLesson002_MyStruct	Test_Struct;
	UPROPERTY(EditAnywhere) UstcMyLesson002_MyObject*	Test_Object = nullptr;
	UPROPERTY(EditAnywhere) EstcMyLesson002_MyEnumClass Test_EnumClass;

	// Sets default values for this actor's properties
	AstcTestActor();

	void demoStrFormat();
	void demoEnum();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
