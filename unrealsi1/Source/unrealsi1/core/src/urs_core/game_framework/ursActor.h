#pragma once

#include "../common/urs_core_common.h"
#include "ursActor.generated.h"

#if 0
#pragma mark --- AursActor-Decl ---
#endif // 0
#if 1

UCLASS()
class UNREALSI1_API AursActor : public AActor
{
	GENERATED_BODY()
public:
	AursActor();

	template<class T> T* createDefault();
	template<class T> T* createDefault(const FString& str);

	template<class T> T* newAttachComponent(USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules = FAttachmentTransformRules::KeepRelativeTransform);
};

template<class T> inline T* AursActor::createDefault()						{ return CreateDefaultSubobject<T>(T::StaticClass()->GetFName()); }
template<class T> inline T* AursActor::createDefault(const FString& str)	{ return CreateDefaultSubobject<T>(FName{*str}); }

template<class T> inline
T* 
AursActor::newAttachComponent(USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules)
{
	T* newComponent = NewObject<T>(this);
	newComponent->RegisterComponent();
	newComponent->AttachToComponent(Parent, FAttachmentTransformRules::KeepRelativeTransform);
	return newComponent;
}

#endif

#if 0
#pragma mark --- ursActorUtil-Decl ---
#endif // 0
#if 1

struct UNREALSI1_API ursActorUtil
{
public:
	template<class T> static T* createDefaultSubObj(AActor* actor);
	template<class T> static T* createDefaultSubObj(AActor* actor, const FString& str);

	template<class T> static T* newAttachComponent(USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules = FAttachmentTransformRules::KeepRelativeTransform);
	template<class T> static T* newAttachComponent_Ctor(AActor* actor, USceneComponent* Parent);
};

template<class T> inline T* ursActorUtil::createDefaultSubObj(AActor* actor)						{ return actor->CreateDefaultSubobject<T>(T::StaticClass()->GetFName()); }
template<class T> inline T* ursActorUtil::createDefaultSubObj(AActor* actor, const FString& str)	{ return actor->CreateDefaultSubobject<T>(FName{*str}); }

template<class T> inline
T* 
ursActorUtil::newAttachComponent(USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules)
{
	T* newComponent = NewObject<T>();
	newComponent->RegisterComponent();
	newComponent->AttachToComponent(Parent, AttachmentRules);
	return newComponent;
}

template<class T> inline
T* 
ursActorUtil::newAttachComponent_Ctor(AActor* actor, USceneComponent* Parent)
{
	T* newComponent = actor->CreateDefaultSubobject<T>(T::StaticClass()->GetFName());
	newComponent->SetupAttachment(Parent);
	return newComponent;
}

#endif