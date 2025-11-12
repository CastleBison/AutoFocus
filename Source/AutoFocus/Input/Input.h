
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Input.generated.h"

UCLASS()
class AUTOFOCUS_API UInput : public UObject
{
	GENERATED_BODY()

public:
	UInput();

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext>	Context;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction>			PawnRotation;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction>			ActionZoom;
};


