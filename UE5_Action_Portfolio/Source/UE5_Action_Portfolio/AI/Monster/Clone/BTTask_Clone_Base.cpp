#include "AI/Monster/Clone/BTTask_Clone_Base.h"
#include "AI/Monster/Clone/AIPlayerCloneCon.h"
#include "Kismet/GamePlayStatics.h"

UBTTask_Clone_Base::UBTTask_Clone_Base()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

ACloneMonster* UBTTask_Clone_Base::GetCloneMonster(UBehaviorTreeComponent& OwnerComp)
{
	AGlobalAICharacter* GlobalAICharacter = GetGlobalAICharacter(OwnerComp);

	ACloneMonster* CloneCharacter = Cast<ACloneMonster>(GlobalAICharacter);

	if (false == IsValid(CloneCharacter))
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> false == IsValid"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	return CloneCharacter;
}

EBTNodeResult::Type UBTTask_Clone_Base::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACloneMonster* CloneMonster = GetCloneMonster(OwnerComp);

	if (false == IsValid(CloneMonster))
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> false == IsValid"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Failed;
	}

	UWeaponComponent* WeaponComponent = CloneMonster->GetWeaponComponent();

	if (false == IsValid(WeaponComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> false == IsValid"), __FUNCTION__, __LINE__);
		return EBTNodeResult::Failed;
	}

	WeaponComponent->WAndSButtonAction(0);
	WeaponComponent->DAndAButtonAction(0);
	WeaponComponent->RollorRunAction(0);
	WeaponComponent->AimorBlockAction(0);

	return EBTNodeResult::InProgress;
}

void UBTTask_Clone_Base::OnGameplayTaskActivated(UGameplayTask&)
{

}

void UBTTask_Clone_Base::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
