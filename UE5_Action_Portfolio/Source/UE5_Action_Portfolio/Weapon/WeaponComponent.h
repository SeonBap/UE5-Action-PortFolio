#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Global/Enums.h"
#include "WeaponComponent.generated.h"

class AArrow;
class UWeaponAction;
class USkeletalMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_ACTION_PORTFOLIO_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

	void SetMeshAttach(USkeletalMeshComponent* _Mesh);
	void ChangeCollisionAttackType();
	void ChangeNoCollision();
	void ArrowSpawn();
	void SetCharacterAirControl(float _Value);
	void SetAttackCheck(bool _Value);
	void SetIsLockOn(bool _Value);
	void SetAttackType(FName _AttackType);
	void SetIsBlock(bool _Value);
	void SetIsParry(bool _Value);
	void SetnullReadyArrow();
	//void SetAnimState(CharacterAnimState _State);
	void IsRollMoveToFalse();
	void ChangeWeapon(FName _Weapon);
	void ChangeSetUnArmed();
	void ChangeSetBow();
	void ChangeSetSwordAndSheiled();
	void PressSpaceBarCkeckAndRoll(float _DeltaTime);
	void WAndSButtonAction(float _Value);
	void DAndAButtonAction(float _Value);
	void RollorRunAction(float _Value);
	void ShiftButtonAction();
	void AttackAction();
	void AimorBlockAtion(float _Value);
	void ParryAction();

	bool GetAttackCheck();
	bool GetIsAimOn();
	bool GetIsRollMove();
	bool GetIsBlock();
	bool GetIsParry();
	bool LockOnAfterRun();

	AArrow* GetReadyArrow();
	FVector GetBowJointLocation();

	//UFUNCTION(BlueprintCallable)
	//CharacterAnimState GetAnimState();
	//UFUNCTION(BlueprintCallable)
	//int GetAnimStateToInt();
	UFUNCTION(BlueprintCallable)
	EWeaponType GetWeaponType();
	UFUNCTION(BlueprintCallable)
	float GetMoveXValue();
	UFUNCTION(BlueprintCallable)
	float GetMoveYValue();
	UFUNCTION(BlueprintCallable)
	bool GetIsLockOn();
	UFUNCTION(BlueprintCallable)
	bool GetIsMove();
	UFUNCTION(BlueprintCallable)
	bool GetLockOnCheck();
	void SetLockOnCheck(bool _Value);

	void GotHit(FVector _Value);
	void Death();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void WeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void BowChordMove();

private:
	CharacterAnimState GetAnimState();
	
public:
	//CharacterAnimState AnimState = CharacterAnimState::Idle;

	// ����
	EWeaponType WeaponType = EWeaponType::UnArmed;

	// ĳ���� ������ ����
	bool BowToSwordAndSheiled = false;
	bool SwordAndSheiledToBow = false;
	bool IsForwardWalk = false;
	bool IsBackwardWalk = false;
	bool IsLeftWalk = false;
	bool IsRightWalk = false;
	bool IsRollMove = false;
	bool IsWalkJump = false;
	bool IsRunJump = false;
	bool IsLockOn = false;
	bool IsAimOn = false;
	bool IsBlock = false;
	bool IsParry = false;
	bool PressSpacebar = false;
	bool AttackCheck = false;
	bool ArrowReady = false;
	bool EarlyArrowCheck = false;
	bool LockOnCheck = false;
	float PressSpacebarTime = 0.f;
	float LockOnAfterRunTime = 0.f;
	const float LockOnAfterRunCount = 2.f;
	const float RunCount = 0.8f;
	const float WalkSpeed = 450.f;
	const float LockOnSpeed = 400.f;
	const float RunSpeed = 700.f;
	const float AimorBlockSpeed = 250.f;
	float MoveXValue = 0.f;
	float MoveYValue = 0.f;
	// ���� �� ����
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* UnArmedWeaponMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BowWeaponMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SwordWeaponMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* ShieldWeaponMesh;

	// ���� ���� ���� ����
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BackBowWeaponMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BackSwordWeaponMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BackShieldWeaponMesh;



private:
	FName AttackType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AArrow> ArrowClass;
	UPROPERTY()
	AArrow* ReadyArrow = nullptr;
};