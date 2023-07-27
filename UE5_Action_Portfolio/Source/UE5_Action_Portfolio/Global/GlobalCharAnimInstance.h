#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Global/Enums.h"
#include "GlobalCharAnimInstance.generated.h"

UCLASS()
class UE5_ACTION_PORTFOLIO_API UGlobalCharAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void MontageBlendingOut(UAnimMontage* Anim, bool Inter);
	UFUNCTION()
	void AnimNotify_RollStop();
	UFUNCTION()
	void AnimNotify_JumpStart();
	UFUNCTION()
	void AnimNotify_ChangeWeapon();
	UFUNCTION()
	void AnimNotify_AttackCheck();
	UFUNCTION()
	void AnimNotify_AimorBlockCheck();
	UFUNCTION()
	void AnimNotify_ArrowReadyCheck();
	UFUNCTION()
	void AnimNotify_ChordToHand();
	UFUNCTION()
	void AnimNotify_BowFire();

	//void JumpToAttackMontageSection(int AttackCount);

protected:
	void NativeInitializeAnimation() override;
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaTime) override;

public:
	CharacterAnimState Animstate = CharacterAnimState::Idle;
	UPROPERTY()
	TMap<CharacterAnimState, UAnimMontage*> AllAnimations;

	float AnimSpeed = 1.f;
};