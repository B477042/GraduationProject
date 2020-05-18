// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Components/ActorComponent.h"
#include "Component_SkillContainer.generated.h"

/*
*	스킬에서 엑터가 날아갈 경우, 저장해두는 컨테이너 역할을 하는 컴포넌트
*	상속시켜서 어떤 스킬에 대한 정보를 저장하는 용도로 사용할 것이다
*	예를 들어 boss의 불을 날리는 행동을 파생시킨다면, 그 밑에는 투사체를 상속받은 발사체들로 가득차있고
*	사용하면 꺼내지는 식으로 작동할 것이다. 예전에 만든 총알 발사 시스템처럼
*
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

	virtual void UseSkill(const AActor& TargetActor, int n_Count) PURE_VIRTUAL(UComponent_SkillContainer::UseSkill,  );

	//주어진 수 만큼 queue에 밀어 넣는다
	template <typename T>
	void AddSkillObj(T* Input, int num);

protected:
	void revolve();
	

protected:
	UPROPERTY(VisibleAnywhere,  Category = "contents", meta = (AllowPrivateAccess = "true"))
		TArray< TWeakObjectPtr< AActor > > SkillObjects;
	UPROPERTY(VisibleAnywhere, Category = "contents", meta = (AllowPrivateAccess = "true"))
		TWeakObjectPtr<AActor> CurrentIndex;
	UPROPERTY(VisibleAnywhere, Category = "contents", meta = (AllowPrivateAccess = "true"))
		int Index;

};
