#include "AI/Boss/BTTask_BossBase.h"

EBTNodeResult::Type UBTTask_BossBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

void UBTTask_BossBase::OnGameplayTaskActivated(UGameplayTask& _Task)
{
}

void UBTTask_BossBase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
