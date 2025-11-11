
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "../Input/Input.h"
#include "AutoFocusPawn.generated.h"

UCLASS()
class AUTOFOCUS_API AAutoFocusPawn : public APawn
{
	GENERATED_BODY()

public:
	AAutoFocusPawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	public:
	void CameraRotationKey(const FInputActionValue& Value);

};
