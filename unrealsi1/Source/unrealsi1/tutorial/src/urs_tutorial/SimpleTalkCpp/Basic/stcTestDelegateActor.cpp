#include "stcTestDelegateActor.h"

void stc_C_Static_Function(int testInt, float testFloat) {
	URS_LOG("C_Static_Function");
}

void AstcTestDelegateActor::OnStaticMemberFunction(int testInt, float testFloat) {
	URS_LOG("OnStaticMemberFunction");
}

void AstcTestDelegateActor::OnTestFunction(int testInt, float testFloat) {
	URS_LOG("OnTestFunction({}, {})", testInt, testFloat);
}

void AstcTestDelegateActor::OnTestUFunction(int testInt, float testFloat) {
	URS_LOG("OnTestUFunction({}, {})", testInt, testFloat);
}

void AstcTestDelegateActor::OnTestDynamicFunction(int testInt, float testFloat) {
	URS_LOG("OnTestDynamicFunction({}, {})", testInt, testFloat);
}

AstcTestDelegateActor::AstcTestDelegateActor() {
	TestEvent.AddStatic(&stc_C_Static_Function);
	TestEvent.AddStatic(&ThisClass::OnStaticMemberFunction);

	TestEvent.AddUObject(this, &ThisClass::OnTestFunction);
	//	TestEvent.AddSP();

	// UFunction for UObject only, when UObject is destroyed by gc, the event entry will also be deleted / not being called
	TestEvent.AddUFunction(this, TEXT("OnTestUFunction"));
	TestEvent.AddUFunction(this, TEXT("OnTestBlueprintImplentableEvent"));

	TestEvent.AddLambda([](int testInt, int testFloat) {
		URS_LOG("OnTest Lambda");
		});
	TestEvent.AddWeakLambda(this, [](int testInt, int testFloat) {
		URS_LOG("OnTest Weak Lambda");
		});

	TestDynamicEvent.AddDynamic(this, &ThisClass::OnTestDynamicFunction);
}

void AstcTestDelegateActor::BeginPlay() {
	Super::BeginPlay();

	URS_LOG("BeginPlay()");

	TestDelegate.ExecuteIfBound(0, 1);
	TestEvent.Broadcast(1, 2);

	TestDynamicDelegate.ExecuteIfBound(3, 4);
	TestDynamicEvent.Broadcast(5, 6);
}

