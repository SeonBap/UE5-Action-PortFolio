#include "AI/AICon.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Global/Enums.h"

AAICon::AAICon()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseSight");

	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	AIPerceptionComponent->SetDominantSense(AISenseConfigSight->GetSenseImplementation());

	// 각 인덱스별로 팀을 구분하고, 팀별로 서로 적대적인지 친구인지 중립인지 구분한다.
	Attitudes = {
		{ETeamAttitude::Friendly, ETeamAttitude::Neutral, ETeamAttitude::Neutral, ETeamAttitude::Neutral, ETeamAttitude::Neutral }, // Neutral
		{ETeamAttitude::Neutral, ETeamAttitude::Friendly, ETeamAttitude::Hostile, ETeamAttitude::Hostile, ETeamAttitude::Hostile }, // PlayerTeam
		{ETeamAttitude::Neutral, ETeamAttitude::Hostile, ETeamAttitude::Friendly, ETeamAttitude::Hostile, ETeamAttitude::Friendly }, // CloneTeam
		{ETeamAttitude::Neutral, ETeamAttitude::Hostile, ETeamAttitude::Hostile, ETeamAttitude::Friendly, ETeamAttitude::Friendly }, // MonsterTeam
		{ETeamAttitude::Neutral, ETeamAttitude::Hostile, ETeamAttitude::Friendly, ETeamAttitude::Friendly, ETeamAttitude::Friendly }, // BossTeam
	};
}

void AAICon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == TargetLost)
	{
		LostTimer += _DeltaTime;
	}

	if (5.f <= LostTimer)
	{
		LostTimer = 0.f;
		TargetLost = false;
		PerceivedActor = nullptr;
		GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), PerceivedActor);
		GetBlackboardComponent()->SetValueAsBool(TEXT("IsReturn"), true);
	}
}

UBehaviorTreeComponent* AAICon::GetBehaviorTreeComponent()
{
	return BehaviorTreeComponent;
}

UBlackboardComponent* AAICon::GetBlackboardComponent()
{
	return BlackboardComponent;
}

UAIPerceptionComponent* AAICon::GetAIPerceptionComponent()
{
	return AIPerceptionComponent;
}

UAISenseConfig_Sight* AAICon::GetAISenseConfigSight()
{
	return AISenseConfigSight;
}

void AAICon::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);
}

void AAICon::BeginPlay()
{
	Super::BeginPlay();

	GetAIPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAICon::OnTargetPerceptionUpdated);
}

ETeamAttitude::Type AAICon::GetTeamAttitudeTowards(const AActor& Other) const
{
	APawn const* OtherPawn = Cast<APawn>(&Other);

	if (false == IsValid(OtherPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> false == IsValid"), __FUNCTION__, __LINE__);
		return ETeamAttitude::Neutral;
	}

	const IGenericTeamAgentInterface* const TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());

	if (nullptr == TeamAgent)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> nullptr == TeamAgent"), __FUNCTION__, __LINE__);
		return ETeamAttitude::Neutral;
	}

	FGenericTeamId CurTeamID = this->GetGenericTeamId();
	FGenericTeamId OtehrTeamID = TeamAgent->GetGenericTeamId();

	bool CurTeamIDValid = Attitudes.IsValidIndex(CurTeamID.GetId());
	bool OtehrTeamIDValid = Attitudes.IsValidIndex(OtehrTeamID.GetId());

	if (true == CurTeamIDValid && true == OtehrTeamIDValid)
	{
		return Attitudes[CurTeamID.GetId()][OtehrTeamID.GetId()];
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
				LostTimer = 0.f;
				TargetLost = false;
				PerceivedActor = _Actor;

			}
			// 인식 했던 적이 있다면
			// ex) 타겟이 새로 들어올 때
			// ex) 인식 범위로 들어온 타겟이 다시 나갈 때
			// ex) 인식 범위를 나갔던 타겟이 다시 들어올 때
			else if (nullptr != PerceivedActor)
			{
				UObject* TargetObject = GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor"));
				AActor* TargetActor = Cast<AActor>(TargetObject);

				if (false == IsValid(TargetActor))
				{
					UE_LOG(LogTemp, Error, TEXT("%S(%u)> false == IsValid"), __FUNCTION__, __LINE__);
					return;
				}

				// 인식 했던 적이 타겟과 같다
				if (_Actor == TargetActor)
				{
					// ex) 인식 범위를 나갔던 타겟이 다시 들어올 때
					if (true == TargetLost)
					{
						LostTimer = 0.f;
						TargetLost = false;
					}
					// ex) 인식 범위로 들어온 타겟이 다시 나갈 때
					else if (false == TargetLost)
					{
						TargetLost = true;
					}
				}
				// 인식 했던 적이 다르다면
				// ex) 다른 타겟이 새로 들어오거나 나갈때
				else
				{
					APawn* CurPawn = GetPawn();

					if (IsValid(CurPawn))
					{
						UE_LOG(LogTemp, Error, TEXT("%S(%u)> false == IsValid"), __FUNCTION__, __LINE__);
						return;
					}

					FVector CurLocation = CurPawn->GetActorLocation();

					FVector PerceivedActorDis = PerceivedActor->GetActorLocation() - CurLocation;
					FVector TargetdActorDis = _Actor->GetActorLocation() - CurLocation;

					// 인식 했던 적보다 새로 인식 된 적이 가깝다면 타겟 변경
					if (PerceivedActorDis.Size() > TargetdActorDis.Size())
					{
						LostTimer = 0.f;
						TargetLost = false;

						PerceivedActor = _Actor;
					}
				}
			}

			GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), PerceivedActor);
		}
		break;
	case _Stimulus.SensingFailed: // 타겟 인식 실패
		PerceivedActor = nullptr;
		GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
		break;
	default:
		return;
		break;
	}
}
