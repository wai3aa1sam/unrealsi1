#pragma once

#include "urs_tutorial/common/urs_tutorial_common.h"
#include "stcTestDelegateActor.generated.h"

DECLARE_DELEGATE_TwoParams(          FnStcTestDelegate, int, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FnStcTestEvent,    int, float);

DECLARE_DYNAMIC_DELEGATE_TwoParams(          FnStcTestDynamicDelegate, int, testInt, float, testFloat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FnStcTestDynamicEvent,    int, testInt, float, testFloat);

UCLASS()
class AstcTestDelegateActor : public AActor 
{
	GENERATED_BODY()
public:

	// weak ref, useful when hold a ref for eg. 3rd person game, lock target
	UPROPERTY() TWeakObjectPtr<AActor> _wUPtr;

	FnStcTestDelegate	TestDelegate;
	FnStcTestEvent		TestEvent;

	// mostly for blueprint
	// Dynamic delegates can be serialized, their functions can be found by name, and they are slower than regular delegates.
	// https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Delegates/Dynamic/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		FnStcTestDynamicDelegate	TestDynamicDelegate;
	UPROPERTY(EditAnywhere, BlueprintAssignable)	FnStcTestDynamicEvent		TestDynamicEvent;

	static void OnStaticMemberFunction(int testInt, float testFloat);

	void OnTestFunction(int testInt, float testFloat);

	UFUNCTION(BlueprintCallable)
	void OnTestUFunction(int testInt, float testFloat); // Blueprint call C++

	UFUNCTION(BlueprintImplementableEvent)
	void OnTestBlueprintImplentableEvent(int testInt, float testFloat); // C++ call Blueprint Event

	UFUNCTION()
	void OnTestDynamicFunction(int testInt, float testFloat);

public:
	AstcTestDelegateActor();
	virtual void BeginPlay() override;
};
