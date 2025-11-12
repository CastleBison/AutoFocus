
#include "Input.h"
#include "UObject/ConstructorHelpers.h"

UInput::UInput()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputContext(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/IA/IMC_AutoFocus.IMC_AutoFocus'"));

	if (InputContext.Succeeded())
	{
		Context = InputContext.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> CameraRotation(TEXT("/Script/EnhancedInput.InputAction'/Game/IA/IA_CameraRotation.IA_CameraRotation'"));

	if (CameraRotation.Succeeded())
	{
		PawnRotation = CameraRotation.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Zoom(TEXT("/Script/EnhancedInput.InputAction'/Game/IA/IA_Zoom.IA_Zoom'"));

	if (Zoom.Succeeded())
	{
		ActionZoom = Zoom.Object;
	}
}
