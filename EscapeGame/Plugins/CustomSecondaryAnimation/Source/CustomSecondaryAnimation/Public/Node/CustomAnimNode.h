// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "UObject/Object.h"
#include "CustomAnimNode.generated.h"

/**
 * 
 */
USTRUCT(BlueprintInternalUseOnly)
struct CUSTOMSECONDARYANIMATION_API FAnimNode_SecondaryAnim : public FAnimNode_SkeletalControlBase
{
	GENERATED_USTRUCT_BODY()
public:
	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)  override;
	// End of FAnimNode_Base interface

	virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;
	virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;
protected:
	// FAnimNode_SkeletalControlBase protected interface
	virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones);
	// End of FAnimNode_SkeletalControlBase protected interface

};
