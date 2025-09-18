// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_SkeletalControlBase.h"
#include "BoneControllers/AnimNode_LookAt.h"
#include "Node/CustomAnimNode.h"

#include "AnimGraphNode_SecondaryAnim.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(Keywords = "Custom"),Category="CustomNode")
class CUSTOMSECONDARYANIMATIONEDITOR_API UAnimGraphNode_SecondaryAnim : public UAnimGraphNode_SkeletalControlBase
{
	GENERATED_BODY()
public:

	
	virtual FLinearColor GetNodeBodyTintColor() const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;


	// UAnimGraphNode_SkeletalControlBase interface
	virtual void Draw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* SkelMeshComp) const override;
	virtual void GetOnScreenDebugInfo(TArray<FText>& DebugInfo, FAnimNode_Base* RuntimeAnimNode, USkeletalMeshComponent* PreviewSkelMeshComp) const override;
	// End of UAnimGraphNode_SkeletalControlBase interface


protected:
	// UAnimGraphNode_SkeletalControlBase interface
	virtual FText GetControllerDescription() const override;
	virtual const FAnimNode_SkeletalControlBase* GetNode() const override { return &Node; }
	// End of UAnimGraphNode_SkeletalControlBase interface
public:
	UPROPERTY(EditAnywhere, Category=Settings)
	FAnimNode_SecondaryAnim Node;
};
