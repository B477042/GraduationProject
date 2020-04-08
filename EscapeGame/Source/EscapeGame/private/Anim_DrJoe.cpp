// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_DrJoe.h"

UAnim_DrJoe::UAnim_DrJoe()
{
	PoseTimer = 0.0f;
	LimitTimer = 3.0f;
}

void UAnim_DrJoe::randState()
{
	int newState = (int)FMath::RandRange(0,4);
	
	switch (newState)
	{
	case 0:
		State = EState::Idle;
		break;
	case 1:
		State = EState::Talking1;
		break;
	case 2:
		State = EState::Talking2;
		break;
	case 3:
		State = EState::Talking3;
		break;
	}

}

UAnimSequence* UAnim_DrJoe::PosePlay(UAnimSequence* input)
{
	return input;
}
