/*
Player CharacterªË?ª¹ªëöâªÎÜâªä«µ«¤«ÈªÎ«½?«¹ªò«³«Ô?ª¹ªëÝ»ÝÂªÇª¹¡£

*/

//==============================================================
//EGPlayerCharacter.cpp
//normalÍô?ªòª¹ªëñé¡¢montage?×âªòû¼ªÓõóª¹Ý»ÝÂ
void AEGPlayerCharacter::ComboAttack()
{

	//ã·ÔÑÔÑíÂ
	if (!Stat->IsAttacking())
	{
		Stat->SetComboStartState();
	 
		Anim->JumpToComboAttackSection(Stat->GetCurrentCombo());
		Anim->PlayAttackMontage();
		
	}
	//ª¹ªÇªËÍô?ñéªÎ?÷¾
	else
	{
		
		if (!Stat->CheckCanComboAttack())
		{
			//ó­ªÎ«â«ó«¿?«¸«åªòî¢ßæªµª»ªë
			Stat->SetComboAttackInput(true);

		}
	}
	
}

//==============================================================
//EGPlayerCharacter.h
//PlayerªÎì¹ÔÑ?×âªËªÄª¤ªÆªÏª³ªÎ«µ«¤«Èªò?ðÎª·ªÞª·ª¿
//=============================================
	//Moving
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Direction", meta = (AllowPrivateAccess = "true"))
		FVector MoveDirection;
	float CurrentVelocity;

//==============================================================
//EGPlayerCharacter.cpp
//PlayerªÎì¹ÔÑ?×âªËªÄª¤ªÆªÏª³ªÎ«µ«¤«Èªò?ðÎª·ªÞª·ª¿

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
// MontageªÇªÉªÎªèª¦ªÊSectionªò«×«ì«¤ª¹ªëª«ªòÌ½ªáªë??
void UAnim_Player::JumpToComboAttackSection(int32 NewSection)
{
	if (!Montage_IsPlaying(AttackMontage))//if not playing attack montage 
		return;
	
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection));
}

//===================================================
// StatComponent_Player.cpp
//Montageî¢ßæªÎª¿ªáªÎ«³«ó«ÜÎ·×â??
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
//Montageî¢ßæªÎª¿ªáªÎ«³«ó«ÜÎ·×â??
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
//PlayerªÎ??ö·«Æ?«Ö«ëªò?ªß?ªà??ªÏÞçª¬õÚÊ¥ª·ªÞª·ª¿¡£
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
//ª³ªÎ«²?«àªÎ?éÄLog Macro
// EscapeGame.h
#define EGLOG_CALLINFO (/*FString( __FILE__)+TEXT("->")+*/FString(__FUNCTION__)+TEXT("(")+FString::FromInt(__LINE__)+TEXT(")"))
#define EGLOG_CALLONLY (Verbosity) UE_LOG(EGgame,Verbosity,TEXT("%s"),*EGLOG_CALLINFO)
#define EGLOG(Verbosity,Format, ...) UE_LOG(EGgame,Verbosity,TEXT("%s %s"),*EGLOG_CALLINFO,*FString::Printf (Format, ##__VA_ARGS__))
