#include "AI/Boss/BTTask_Boss_Attack_SpawnTornado.h"

EBTNodeResult::Type UBTTask_Boss_Attack_SpawnTornado::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

    AGlobalCharacter* Character = GetGlobalCharacter(OwnerComp);

    if (nullptr == Character)
    {
        return EBTNodeResult::Failed;
    }

    Character->SetAnimState(BossAnimState::Attack_SpawnTornado);

	return EBTNodeResult::InProgress;
}

void UBTTask_Boss_Attack_SpawnTornado::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    AGlobalCharacter* Character = GetGlobalCharacter(OwnerComp);

    if (nullptr == Character)
    {
        return;
    }

    UAnimMontage* Montage = Character->GetAnimMontage(Character->GetAnimState());
    float Time = Montage->CalculateSequenceLength();

    if (Time <= GetStateTime(OwnerComp))
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}