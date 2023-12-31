#include "AI/Boss/BTTask_Boss_Teleport_Rand.h"

EBTNodeResult::Type UBTTask_Boss_Teleport_Rand::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    UBlackboardComponent* Blackboard = GetBlackboardComponent(OwnerComp);

    if (false == IsValid(Blackboard))
    {
        UE_LOG(LogTemp, Error, TEXT("%S(%u)> false == IsValid"), __FUNCTION__, __LINE__);
        return EBTNodeResult::Failed;
    }

    int Rand = UGlobalGameInstance::MainRandom.RandRange(0, 2);

    if (0 == Rand)
    {
        return EBTNodeResult::Succeeded;
    }
    else
    {
        return EBTNodeResult::Failed;
    }
    
    return EBTNodeResult::Failed;
}

void UBTTask_Boss_Teleport_Rand::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
