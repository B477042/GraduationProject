// Fill out your copyright notice in the Description page of Project Settings.


#include "Node/CustomAnimNode.h"

void FAnimNode_SecondaryAnim::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	FAnimNode_SkeletalControlBase::Initialize_AnyThread(Context);
}

void FAnimNode_SecondaryAnim::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	FAnimNode_SkeletalControlBase::CacheBones_AnyThread(Context);
}

void FAnimNode_SecondaryAnim::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output,
	TArray<FBoneTransform>& OutBoneTransforms)
{
	FAnimNode_SkeletalControlBase::EvaluateSkeletalControl_AnyThread(Output, OutBoneTransforms);
}

void FAnimNode_SecondaryAnim::PreUpdate(const UAnimInstance* InAnimInstance)
{
	FAnimNode_SkeletalControlBase::PreUpdate(InAnimInstance);
}

void FAnimNode_SecondaryAnim::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
	FAnimNode_SkeletalControlBase::InitializeBoneReferences(RequiredBones);
}

bool FAnimNode_SecondaryAnim::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
{
	return FAnimNode_SkeletalControlBase::IsValidToEvaluate(Skeleton, RequiredBones);
}
