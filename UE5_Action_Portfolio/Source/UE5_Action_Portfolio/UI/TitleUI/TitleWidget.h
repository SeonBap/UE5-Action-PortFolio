#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

UCLASS()
class UE5_ACTION_PORTFOLIO_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetPressAnyKeyWidgetOnOff(bool _Value);
	UFUNCTION(BlueprintCallable)
	void SetLogoWidgetOnOff(bool _Value);
	UFUNCTION(BlueprintCallable)
	void SetMenuButtenWidgetOnOff(bool _Value);

protected:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility PressAnyKeyWidgetOnOff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility LogoWidgetOnOff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility MenuButtenWidgetOnOff;
};
