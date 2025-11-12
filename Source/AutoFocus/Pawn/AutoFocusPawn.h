
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "../Input/Input.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
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
	void ZoomKey(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent>	SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent>	Camera;



	
protected:
	UPROPERTY(EditAnywhere)
	float DefaultFOV = 90.f;

	UPROPERTY(EditAnywhere)
	float ZoomFOV = 45.f;

	UPROPERTY(EditAnywhere)
	float ZoomInterpSpeed = 3.f;

	float AutoFocusTraceDistance = 5000.f;

	float FocusLocation = 0.f;

	float AutoFocusSpeed = 10.f;

private:
	bool bIsZoom = false;

};
