// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/AnimGraphNode_SecondaryAnim.h"




FLinearColor UAnimGraphNode_SecondaryAnim::GetNodeBodyTintColor() const
{
	return FLinearColor::Red;
}

FLinearColor UAnimGraphNode_SecondaryAnim::GetNodeTitleColor() const
{
	return FLinearColor(FColor::Magenta);
}

FText UAnimGraphNode_SecondaryAnim::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("Hello My Custom Node"));
}

void UAnimGraphNode_SecondaryAnim::Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* SkelMeshComp) const
{
	Super::Draw(PDI, SkelMeshComp);
}

void UAnimGraphNode_SecondaryAnim::GetOnScreenDebugInfo(TArray<FText>& DebugInfo, FAnimNode_Base* RuntimeAnimNode,
	USkeletalMeshComponent* PreviewSkelMeshComp) const
{
	Super::GetOnScreenDebugInfo(DebugInfo, RuntimeAnimNode, PreviewSkelMeshComp);
}

FText UAnimGraphNode_SecondaryAnim::GetControllerDescription() const
{
	return Super::GetControllerDescription();
}
