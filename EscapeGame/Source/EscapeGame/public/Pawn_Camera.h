// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "GameFramework/Pawn.h"
//#include "NPCCharacter.h"
#include "Engine/DataTable.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"

#include "Pawn_Camera.generated.h"



USTRUCT(BlueprintType)
struct FDialogueTableRow : public FTableRowBase
{
	GENERATED_BODY()
	public:
	//대사 내용
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FString Dialogue;
	//화자
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	FText Talker;
	//몇 번재 Act인지, 미사용
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	int32 n_Act;
	//몇 번째 대사인지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
	int32 Line;
};

/*
	대화를 하는 장면을 촬영하는 pawn
	대화가 일어나는 스크립트는 여기에 저장되고
	next prev 버튼에 대한 상호작용으로
	넘어가는 대화도 여기서 처리한다.
	버튼을 누르는 이벤트로 대상이 되는 캐릭터에 움직임을 준다.


*/
UCLASS()
class ESCAPEGAME_API APawn_Camera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawn_Camera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//대화하는 상대의 말을 듣게 된다
	void AddTalkingActor(TWeakObjectPtr<class ANPCCharacter> Talker);
	//말을 걸어오기 시작할 때 호출합니다
	void StartListenTo(TWeakObjectPtr<class ANPCCharacter>Talker);
	
	//빙의될 때 위젯에 델리게이트를 등록한다
	UFUNCTION(BlueprintCallable)
	void OnNextClicked();
	//빙의될 때 위젯에 델리게이트를 등록한다
	UFUNCTION(BlueprintCallable)
	void OnPrevClicked();

private:
	
	//상황에 맞는 대화 목록을 불러옵니다.
	void loadDialogue();
	//처음 화면에 띄울때만 사용한다
	void startTalk();
	void nextLog();
	void prevLog();
	//지금 출력해야될 내용 출력
	void printLog();
	void registDelegateToWidget();
	class UDialogueWidget* getWidget();
private:
	UPROPERTY(EditAnywhere)
		UCameraComponent* Cam;
	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollision;
	//Array of Talkers. 
	UPROPERTY(VisibleAnywhere, Category = "DialogueInfo")
	TArray<TWeakObjectPtr<ANPCCharacter>  >a_Talkers;
	UPROPERTY(VisibleAnywhere, Category = "DialogueInfo", meta = (AllowPrivateAccess = "true"))
	class UDataTable*  dialogueTable;
	/*UPROPERTY(VisibleAnywhere, Category = "DialogueInfo", meta = (AllowPrivateAccess = "true"))
		TArray< class UDataTable* > dialogueTable;*/
	UPROPERTY(VisibleAnywhere, Category = "DialogueInfo", meta = (AllowPrivateAccess = "true"))
		TArray< FDialogueTableRow>dialogues;
	//막의 구성을 n_Act로 구현한다
	//static int n_Act;
	//대화를 Log로 출력할 때 줄의 숫자. 대화에서 처음 대사는 0번이 된다
	UPROPERTY(Transient, VisibleAnywhere, Category = "DialogueInfo")
	uint32 c_Talk;
	//지금 다이얼로그의 대사 총 대사 갯수. 6줄이면 5가 될 것이다
	UPROPERTY(Transient, VisibleAnywhere, Category = "DialogueInfo")
	uint32 maxLine;
	
	bool bIsDelegateRegist;
	
};


