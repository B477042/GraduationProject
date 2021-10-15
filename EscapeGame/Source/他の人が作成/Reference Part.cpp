/*
Player Character��?���������䫵���ȪΫ�?���򫳫�?����ݻ�ªǪ���

*/

//==============================================================
//EGPlayerCharacter.cpp
//normal��?�򪹪��顢montage?���������ݻ��
void AEGPlayerCharacter::ComboAttack()
{

	//�������
	if (!Stat->IsAttacking())
	{
		Stat->SetComboStartState();
	 
		Anim->JumpToComboAttackSection(Stat->GetCurrentCombo());
		Anim->PlayAttackMontage();
		
	}
	//���Ǫ���?���?��
	else
	{
		
		if (!Stat->CheckCanComboAttack())
		{
			//�Ϋ��?�������檵����
			Stat->SetComboAttackInput(true);

		}
	}
	
}

//==============================================================
//EGPlayerCharacter.h
//Player�����?��˪Ī��ƪϪ��Ϋ����Ȫ�?�Ϊ��ު���
//=============================================
	//Moving
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Direction", meta = (AllowPrivateAccess = "true"))
		FVector MoveDirection;
	float CurrentVelocity;

//==============================================================
//EGPlayerCharacter.cpp
//Player�����?��˪Ī��ƪϪ��Ϋ����Ȫ�?�Ϊ��ު���

void AEGPlayerCharacter::UpDown( float  NewAxisValue)
{
 
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Direction.Z = 0.0f;
	Direction.Normalize();
	MoveDirection += Direction * FMath::Clamp(NewAxisValue, -1.0f, 1.0f);
		
}

void AEGPlayerCharacter::LeftRight( float NewAxisValue)
{
	
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	Direction.Z = 0.0f;
	Direction.Normalize();
	MoveDirection += Direction * FMath::Clamp(NewAxisValue, -1.0f, 1.0f);

}

void AEGPlayerCharacter::Move(float DeltaTime)
{
	if (MoveDirection.IsZero()) {
		return;
	}

	MoveDirection.Normalize();
	AddMovementInput(MoveDirection, CurrentVelocity * DeltaTime);
	MoveDirection.Set(0.0f, 0.0f, 0.0f);
}

//===================================================
// Anim_Player.cpp
// Montage�ǪɪΪ誦��Section��׫쫤���몫��̽���??
void UAnim_Player::JumpToComboAttackSection(int32 NewSection)
{
	if (!Montage_IsPlaying(AttackMontage))//if not playing attack montage 
		return;
	
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection));
}

//===================================================
// StatComponent_Player.cpp
//Montage���Ϊ���Ϋ����η��??
void UStatComponent_Player::SetComboStartState()
{
	bCanChargeAttack = true;
	bCanComboAttack = true;
	bIsAttacking = true;

	AddCombo(1);

	bIsChargeAttackInputOn = false;
	bIsComboAttackInputOn = false;

	SetDontMove();
}
//Montage���Ϊ���Ϋ����η��??
void UStatComponent_Player::SetComboEndState()
{

	bCanComboAttack = false;
	bCanChargeAttack = false;
	bIsAttacking = false;
	
	bIsChargeAttackInputOn = false;
	bIsComboAttackInputOn = false;
	ResetCombo();

	SetWalking();
}

//===================================================
//StatComponent_Player.cpp
//Player��??����?�֫��?��?��??���窬��ʥ���ު�����
void UStatComponent_Player::LoadLevelData()
{

	auto OwnerChara = Cast<ACharacter>(GetOwner());
	if (OwnerChara == nullptr)
	{
		EGLOG(Warning, TEXT("Owner is not Character class"));
		return;
	}
	auto OwnerCon = Cast<AEGPlayerController>(OwnerChara->Controller);
	if (OwnerCon == nullptr)
	{
		EGLOG(Warning, TEXT("Owner controller Casting failed"));
		return;
	}

	auto DataTable = OwnerCon->GetDT_Player();

	FPlayerTableRow* PlayerTableRow;

	if (!DataTable)
	{
		EGLOG(Error, TEXT("Table row null"));
		return;
	}
	PlayerTableRow = DataTable->FindRow<FPlayerTableRow>(FName(*(FString::FormatAsNumber(Level))), FString(""));

	MaxHP = PlayerTableRow->MaxHp;
	CurrentHP = MaxHP;
	NextExp = PlayerTableRow->NextExp;
	CurrentATK = PlayerTableRow->Atk;
	ItemSlot = PlayerTableRow->Slot;
	HPChangedDelegate.Broadcast();
}

//===================================================
//���Ϋ�?���?��Log Macro
// EscapeGame.h
#define EGLOG_CALLINFO (/*FString( __FILE__)+TEXT("->")+*/FString(__FUNCTION__)+TEXT("(")+FString::FromInt(__LINE__)+TEXT(")"))
#define EGLOG_CALLONLY (Verbosity) UE_LOG(EGgame,Verbosity,TEXT("%s"),*EGLOG_CALLINFO)
#define EGLOG(Verbosity,Format, ...) UE_LOG(EGgame,Verbosity,TEXT("%s %s"),*EGLOG_CALLINFO,*FString::Printf (Format, ##__VA_ARGS__))
