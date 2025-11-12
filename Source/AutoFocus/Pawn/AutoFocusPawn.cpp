
#include "AutoFocusPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"


AAutoFocusPawn::AAutoFocusPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SetRootComponent(SpringArm);
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 0.f;
	
	Camera->bUsePawnControlRotation = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;


	// 카메라 포스트프로세스 세팅
	Camera->PostProcessSettings.bOverride_DepthOfFieldFstop = true;
	Camera->PostProcessSettings.bOverride_DepthOfFieldMinFstop = true;
	Camera->PostProcessSettings.bOverride_DepthOfFieldSqueezeFactor = true;
	Camera->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	Camera->PostProcessSettings.bOverride_DepthOfFieldDepthBlurAmount = true;
	Camera->PostProcessSettings.bOverride_DepthOfFieldDepthBlurRadius = true;
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


	// 줌 할때 FOV 변경
	float FOV = bIsZoom ? ZoomFOV : DefaultFOV;
	float NewFOV = FMath::FInterpTo(Camera->FieldOfView, FOV, DeltaTime, ZoomInterpSpeed);
	Camera->SetFieldOfView(NewFOV);

	if (bIsZoom)
	{
		FVector Start = Camera->GetComponentLocation();

		FVector End = (Camera->GetForwardVector() * AutoFocusTraceDistance) + Start;

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);

		FHitResult HitResult;

		UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, ETraceTypeQuery::TraceTypeQuery1, true, ActorsToIgnore,
			EDrawDebugTrace::None, HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.f);

		FVector HitLocation = HitResult.Location - Camera->GetComponentLocation();
	
		float HitLocationLength = HitLocation.Size();

		FocusLocation = FMath::FInterpTo(FocusLocation, HitLocationLength, DeltaTime, AutoFocusSpeed);
	}
	
	else 
	{
		FocusLocation = 0.f;
	}


	Camera->PostProcessSettings.DepthOfFieldFstop = 3.0f;
	Camera->PostProcessSettings.DepthOfFieldMinFstop = 11.f;
	Camera->PostProcessSettings.DepthOfFieldSqueezeFactor = 2.f;
	Camera->PostProcessSettings.DepthOfFieldFocalDistance = FocusLocation;
	Camera->PostProcessSettings.DepthOfFieldDepthBlurAmount = 10.f;
	Camera->PostProcessSettings.DepthOfFieldDepthBlurRadius = 1.f;

	
}

void AAutoFocusPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(EnhancedInput))
	{
		const UInput* InputCDO = GetDefault<UInput>();

		EnhancedInput->BindAction(InputCDO->PawnRotation, ETriggerEvent::Triggered, this, &AAutoFocusPawn::CameraRotationKey);

		EnhancedInput->BindAction(InputCDO->ActionZoom, ETriggerEvent::Triggered, this, &AAutoFocusPawn::ZoomKey);
	}
}

void AAutoFocusPawn::CameraRotationKey(const FInputActionValue& Value)
{
	const FVector Axis = Value.Get<FVector>();

	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y * -1.f);
}

void AAutoFocusPawn::ZoomKey(const FInputActionValue& Value)
{
	bIsZoom = Value.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("Pressed: %d"), Value.Get<bool>());
}

