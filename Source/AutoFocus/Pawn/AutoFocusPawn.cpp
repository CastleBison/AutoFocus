
#include "AutoFocusPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"


AAutoFocusPawn::AAutoFocusPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAutoFocusPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (IsValid(PlayerController))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		const UInput* InputCDO = GetDefault<UInput>();

		Subsystem->AddMappingContext(InputCDO->Context, 0);
	}
}

void AAutoFocusPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAutoFocusPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(EnhancedInput))
	{
		const UInput* InputCDO = GetDefault<UInput>();

		EnhancedInput->BindAction(InputCDO->PawnRotation,
								  ETriggerEvent::Triggered,
								  this,
								  &AAutoFocusPawn::CameraRotationKey);
	}
}

void AAutoFocusPawn::CameraRotationKey(const FInputActionValue& Value)
{
	const FVector Axis = Value.Get<FVector>();

	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y * -1.f);
}

