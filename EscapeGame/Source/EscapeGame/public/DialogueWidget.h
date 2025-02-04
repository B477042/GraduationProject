// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UMG/Public/Components/EditableTextBox.h"
#include "UMG/Public/Components/EditableText.h"

#include "DialogueWidget.generated.h"

/**
 *	
 *	다이얼로그 용 위젯 ui의 클래스
 *	
 *
 *
 */



//대화가 일어날 때 호출시킬 델리게이트. 처음으로 호출된다
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTalkeInvoke);
//next 버튼이 클릭되면 호출 시킬 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickNext);
//prev 버튼이 클릭되면 호출 될 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickPrev);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickSkip);

UCLASS()
class ESCAPEGAME_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable,Category=Talker)
		void SetTalkerName(FText Name);
	UFUNCTION(BlueprintCallable, Category = Talker)
	void PrintLog(FText Diagram);
	
	FOnTalkeInvoke OnTalkeInvokeDelegate;
	UPROPERTY(BlueprintAssignable, Category = "custom")
	FOnClickNext OnClickNextDelegate;
	UPROPERTY(BlueprintAssignable, Category = "custom")
	FOnClickPrev OnClickPrevDelegate;
	UPROPERTY(BlueprintAssignable, Category = "custom")
	FOnClickSkip OnClickSkipDelegate;
	UPROPERTY(BlueprintReadWrite, Category = "info")
	FName NextStage;
	UPROPERTY(BlueprintReadWrite, Category = "info")
	int n_Act;
protected:
	virtual void NativeConstruct()override;

protected:
	UPROPERTY(BlueprintReadOnly)
		class UButton* NextButton;
	UPROPERTY(BlueprintReadOnly)
		class UButton* PrevButton;
	UPROPERTY(BlueprintReadOnly)
		class UButton* ContinueButton;
	UPROPERTY(BlueprintReadOnly)
		class UEditableTextBox* TalkerBox;
	UPROPERTY(BlueprintReadOnly)
	class UEditableText* TextDialogue;
	/*UPROPERTY()
		TWeakObjectPtr<AActor> Talker;*/
		
	
	
private:
	UFUNCTION()
		void OnNextClicked();
	UFUNCTION()
		void OnPrevClicked();
	UFUNCTION()
		void OnContinueClicked();
	//다음 스텡
	UPROPERTY(BlueprintReadWrite, Category = "Key", meta = (AllowPrivateAccess = "true"))
		bool bIsAllowToNext;
};
