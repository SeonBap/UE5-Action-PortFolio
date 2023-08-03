#include "AI/AICon.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Character/PlayerCon.h"
#include "Global/GlobalAICharacter.h"

AAICon::AAICon()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseSight");
	
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfigSight->SightRadius = 1500.f;
	AISenseConfigSight->LoseSightRadius = 2000.f;
	AISenseConfigSight->PeripheralVisionAngleDegrees = 90.f;
	AISenseConfigSight->SetMaxAge(5.f);

	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	AIPerceptionComponent->SetDominantSense(AISenseConfigSight->GetSenseImplementation());

	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

void AAICon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AAICon::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	if (nullptr == BehaviorTreeComponent && false == BehaviorTreeComponent->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == BehaviorTreeComponent && false == BehaviorTreeComponent->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return;
	}

	AGlobalAICharacter* AIPawn = Cast<AGlobalAICharacter>(_InPawn);

	UBehaviorTree* BehaviorTree = AIPawn->GetBehaviorTree();

	if (nullptr == BehaviorTree || false == BehaviorTree->IsValidLowLevel())
	{
		return;
	}

	BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	BlackboardComponent->SetValueAsObject(TEXT("SelfActor"), _InPawn);

	BehaviorTreeComponent->StartTree(*BehaviorTree);
}

void AAICon::BeginPlay()
{
	Super::BeginPlay();

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAICon::OnTargetPerceptionUpdated);
}

ETeamAttitude::Type AAICon::GetTeamAttitudeTowards(const AActor& Other) const
{
	APawn const* OtherPawn = Cast<APawn>(&Other);

	if (nullptr != OtherPawn)
	{	
		// 왜 nullptr이 계속 리턴되는가????
		const IGenericTeamAgentInterface* const TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());

		if (nullptr != TeamAgent)
		{
			FGenericTeamId OtehrTeamID = TeamAgent->GetGenericTeamId();

			if (1 == OtehrTeamID)
			{
				return ETeamAttitude::Friendly;
			}
			else
			{
				return ETeamAttitude::Hostile;
			}

		}
	}
	return ETeamAttitude::Neutral;
}

void AAICon::OnTargetPerceptionUpdated(AActor* _Actor, FAIStimulus _Stimulus)
{
	switch (_Stimulus.Type)
	{
	case _Stimulus.SensingSucceeded: // 타겟 인식 성공
		// 인식한 타겟이 적이라면
		if (ETeamAttitude::Hostile == GetTeamAttitudeTowards(*_Actor))
		{
			// 인식 했던 적이 없다면
			if (nullptr == PerceivedActor)
			{
				PerceivedActor = _Actor;

			}
			// 인식 했던 적이 있다면
			// ex) 타겟이 새로 들어올 때
			// ex) 인식 범위로 들어온 타겟이 다시 나갈 때
			else if (nullptr != PerceivedActor)
			{
				UObject* TargetObject = BlackboardComponent->GetValueAsObject(TEXT("TargetActor"));
				AActor* TargetActor = Cast<AActor>(TargetObject);

				// 인식 했던 적이 타겟과 같다
				// ex) 인식 범위로 들어온 타겟이 다시 나갈 때
				if (_Actor == TargetActor)
				{
					// 일정 시간 후에 nullptr로 변경
					PerceivedActor = nullptr;
				}
				// 인식 했던 적이 다르다면
				// ex) 타겟이 새로 들어올 때
				else
				{
					FVector CurLocation = GetOwner()->GetActorLocation();

					FVector PerceivedActorDis = PerceivedActor->GetActorLocation() - CurLocation;
					FVector TargetdActorDis = _Actor->GetActorLocation() - CurLocation;

					// 인식 했던 적보다 새로 인식 된 적이 가깝다면 타겟 변경
					if (PerceivedActorDis.Size() > TargetdActorDis.Size())
					{
						PerceivedActor = _Actor;
					}
				}
			}

			BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), PerceivedActor);
		}
		break;
	case _Stimulus.SensingFailed: // 타깃 인식 실패
		PerceivedActor = nullptr;
		BlackboardComponent->SetValueAsObject(TEXT("TargetActor"), nullptr);
		break;
	default:
		return;
		break;
	}
	
}
