// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "SkillActor.h"
#include "Components/ActorComponent.h"
#include "Component_SkillContainer.generated.h"

/*
*	스킬에서 엑터가 날아갈 경우, 저장해두는 컨테이너 역할을 하는 컴포넌트
*	상속시켜서 어떤 스킬에 대한 정보를 저장하는 용도로 사용할 것이다
*	예를 들어 boss의 불을 날리는 행동을 파생시킨다면, 그 밑에는 투사체를 상속받은 발사체들로 가득차있고
*	사용하면 꺼내지는 식으로 작동할 것이다. 예전에 만든 총알 발사 시스템처럼
*	TArray 내부에서 회전하듯 돌아가야 된다
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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void UseSkill(const AActor& TargetActor,const FVector& Direction , int n_Count=1) PURE_VIRTUAL(UComponent_SkillContainer::UseSkill,  );

	//주어진 수 만큼 queue에 밀어 넣는다. 같은 타입으로 만들어야 돼서 템플릿을 사용한다
	template <typename T>
	void AddSkillObj(T* Input, int num);
	//TArray< TWeakObjectPtr< ASkillActor > >GetObjs() { return SkillObjects; }
	

protected:
	
	void revolve();
	void clear();

protected:
	UPROPERTY(EditAnywhere, Category = "contents", meta = (AllowPrivateAccess = "true"))
		TArray< TWeakObjectPtr< ASkillActor > > SkillObjects;
	UPROPERTY(VisibleAnywhere, Category = "contents", meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<AActor> CurrentIndex;
	UPROPERTY(VisibleAnywhere, Category = "contents", meta = (AllowPrivateAccess = "true"))
		int Index;

};
