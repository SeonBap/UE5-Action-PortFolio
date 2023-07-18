#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Character.h"
#include "Global/Enums.h"
#include "WeaponAction.generated.h"

UCLASS()
class UE5_ACTION_PORTFOLIO_API UWeaponAction : public UObject
{
	GENERATED_BODY()
	
public:
	UWeaponAction();
	

	void SetCurCharacter(ACharacter* _CurChar);

	MainCharacterAnimState* GetAnimState();
	void SetAnimState(MainCharacterAnimState _State);

	void IsRollMoveToFalse();
	void ChangeWeapon(FName _Weapon);
	void ChangeSetUnArmed();
	void ChangeSetBow();
	void ChangeSetSwordAndSheiled();
	void PressSpaceBarCkeck(float _DeltaTime);

	virtual void WAndSButtonAction(float _Value);
	virtual void DAndAButtonAction(float _Value);
	virtual void RollorRunAction(float _Value);
	virtual void ShiftButtonAction();

	virtual void BeginPlay();

public:
	// 캐릭터
	UPROPERTY()
	ACharacter* CurCharacter;
	MainCharacterAnimState AnimState = MainCharacterAnimState::Idle;

	// 캐릭터 움직임 상태
	bool IsForwardWalk;
	bool IsLeftWalk;
	bool IsRollMove;
	bool IsWalkJump;
	bool IsRunJump;
	bool PressSpacebar;
	float PressSpacebarTime;
	int RunCount;
};
