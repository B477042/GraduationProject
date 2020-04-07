// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "UMG/Public/Components/EditableTextBox.h"
#include "EditableTextBox.h"
#include "DialogueWidget.generated.h"

/**
 *	
 *	다이얼로그 용 위젯 ui의 클래스
 *	
 *
 *
 */
//대화가 일어날 때 호출시킬 델리게이트. 처음으로 호출된다
DECLARE_MULTICAST_DELEGATE(FOnTalkeInvoke);
//next 버튼이 클릭되면 호출 시킬 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnClickNext);
//prev 버튼이 클릭되면 호출 될 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnClickPrev);

UCLASS()
class ESCAPEGAME_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable,Category=Talker)
		void SetTalker(AActor* Other,FText Name);
	
	
	FOnTalkeInvoke OnTalkeInvokeDelegate;
	FOnClickNext OnClickNextDelegate;
	FOnClickPrev OnClickPrevDelegate;
protected:
	virtual void NativeConstruct()override;

protected:
	UPROPERTY()
		class UButton* NextButton;
	UPROPERTY()
		class UButton* PrevButton;
	UPROPERTY()
		class UButton* ContinueButton;
	UPROPERTY()
		class UEditableTextBox* TalkerBox;

	UPROPERTY()
		TWeakObjectPtr<AActor> Talker;
		

	
private:
	UFUNCTION()
		void OnNextClicked();
	UFUNCTION()
		void OnPrevClicked();
	UFUNCTION()
		void OnContinueClicked();
	UPROPERTY(BlueprintReadWrite, Category = "Key", meta = (AllowPrivateAccess = "true"))
		bool bIsAllowToNext;
};
