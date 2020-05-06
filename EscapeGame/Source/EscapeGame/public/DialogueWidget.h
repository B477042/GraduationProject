// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "UMG/Public/Components/EditableTextBox.h"
#include "UMG/Public/Components/EditableText.h"
#include "EditableTextBox.h"
#include "DialogueWidget.generated.h"

/**
 *	
 *	���̾�α� �� ���� ui�� Ŭ����
 *	
 *
 *
 */
//��ȭ�� �Ͼ �� ȣ���ų ��������Ʈ. ó������ ȣ��ȴ�
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTalkeInvoke);
//next ��ư�� Ŭ���Ǹ� ȣ�� ��ų ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickNext);
//prev ��ư�� Ŭ���Ǹ� ȣ�� �� ��������Ʈ
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
	FOnClickNext OnClickNextDelegate;
	FOnClickPrev OnClickPrevDelegate;
	FOnClickSkip OnClickSkipDelegate;
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
	class UEditableText* TextDiagram;
	/*UPROPERTY()
		TWeakObjectPtr<AActor> Talker;*/
		

	
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
