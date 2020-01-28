// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EscapeGame.h"
#include "Blueprint/UserWidget.h"
#include "TittleWidget.generated.h"

/**
 * 

 Tittle 화면의 위젯을 다루는 Class

 */
UCLASS()
class ESCAPEGAME_API UTittleWidget : public UUserWidget
{
	GENERATED_BODY()
public:

protected:
	//void BeginPlay()override;
	void NativeConstruct()override;

	//Start Button Property
	UPROPERTY()
		class UButton* BTN_Start;
	//Load Button Property
	UPROPERTY()
		class UButton* BTN_Load;
	//Option Button Property
	UPROPERTY()
		class UButton* BTN_Option;
	//Exit Button Property
	UPROPERTY()
		class UButton* BTN_Exit;

private:
	//Start Button Click Event
	UFUNCTION()
		void StartNew();
	//Load Button Click Event
	UFUNCTION()
		void LoadGame();
	//Load Option
	UFUNCTION()
		void OpenOption();
	UFUNCTION()
		void ExitGame();

	
};
