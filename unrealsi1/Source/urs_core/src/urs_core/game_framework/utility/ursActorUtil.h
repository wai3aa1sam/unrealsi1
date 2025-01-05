#pragma once

#include "urs_core/common/urs_core_common.h"


#if 0
#pragma mark --- ursActorUtil-Decl ---
#endif // 0
#if 1

struct UNREALSI1_API ursActorUtil
{
public:
	template<class T> static T* createDefault(AActor* actor);
	template<class T> static T* createDefault(AActor* actor, const FString& str);

	template<class T> static T* createDefaultSubObj(AActor* actor);
	template<class T> static T* createDefaultSubObj(AActor* actor, const FString& str);
	template<class T> static T* createDefaultSubObjTo(T*& out, AActor* actor);
	template<class T> static T* createDefaultSubObjTo(TObjectPtr<T>& out, AActor* actor);

	template<class T> static T* newAttachComponent(AActor* actor, USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules = FAttachmentTransformRules::KeepRelativeTransform);
	template<class T> static T* newAttachComponent_Ctor(AActor* actor, USceneComponent* Parent);
};

template<class T> inline T* ursActorUtil::createDefault(AActor* actor)								{ return actor->CreateDefaultSubobject<T>(T::StaticClass()->GetFName()); }
template<class T> inline T* ursActorUtil::createDefault(AActor* actor, const FString& str)			{ return actor->CreateDefaultSubobject<T>(FName{*str}); }

template<class T> inline T* ursActorUtil::createDefaultSubObj(AActor* actor)						{ return actor->CreateDefaultSubobject<T>(T::StaticClass()->GetFName()); }
template<class T> inline T* ursActorUtil::createDefaultSubObj(AActor* actor, const FString& str)	{ return actor->CreateDefaultSubobject<T>(FName{*str}); }
template<class T> inline T* ursActorUtil::createDefaultSubObjTo(T*& out, AActor* actor)				{ out = createDefaultSubObj<T>(actor); return out; }
template<class T> inline T* ursActorUtil::createDefaultSubObjTo(TObjectPtr<T>& out, AActor* actor)	{ out = createDefaultSubObj<T>(actor); return out; }

template<class T> inline
T* 
ursActorUtil::newAttachComponent(AActor* actor, USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules)
{
	T* newComponent = NewObject<T>(actor);
	newComponent->RegisterComponent();
	newComponent->AttachToComponent(Parent, AttachmentRules);
	actor->AddInstanceComponent(newComponent);
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