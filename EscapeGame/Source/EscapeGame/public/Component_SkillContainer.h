// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "SkillActor.h"
#include "Components/ActorComponent.h"
#include "Component_SkillContainer.generated.h"

/*
*	스킬로서 사용되는 Actor들을 저장해두는 컨테이너 역할을 하는 컴포넌트
*	상속시켜서 어떤 스킬에 대한 정보를 저장하는 용도로 사용합니다
*	예를 들어 Boss의 Fireball을 담아두고 싶으면 그것으로 파생 시킵니다.
*	사용해서 꺼내지는 식으로 작동합니다. 
*	TArray 내부에서 회전하듯 돌아갑니다.
*/


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UComponent_SkillContainer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponent_SkillContainer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//Called before destroying the object.
		virtual void BeginDestroy()override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void UseSkill(const AActor& TargetActor,const FVector& Direction , int n_Count=1) PURE_VIRTUAL(UComponent_SkillContainer::UseSkill,  );
	void AddSkillObj(TWeakObjectPtr<ASkillActor> Input);
	//TArray< TWeakObjectPtr< ASkillActor > >GetObjs() { return SkillObjects; }
	int GetCapacity() { return ArraySize; }

	

protected:
	
	void revolve();
	void clear();

protected:
	UPROPERTY(EditAnywhere,  Category = "contents", meta = (AllowPrivateAccess = "true"))
		TArray< TWeakObjectPtr< ASkillActor > > SkillObjects;
	UPROPERTY(VisibleAnywhere, Category = "contents", meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr < ASkillActor> CurrentIndex;
	UPROPERTY(VisibleAnywhere, Category = "contents", meta = (AllowPrivateAccess = "true"))
		int Index;
	//배열 초기화 크기. 늘어나진 않는다
	UPROPERTY(VisibleAnywhere, Category = "contents", meta = (AllowPrivateAccess = "true"))
		int ArraySize;

};
