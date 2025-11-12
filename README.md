# AutoFocus (UE5, C++ + Enhanced Input)

레벨 카메라를 Pawn으로 구성해 줌(Zoom) 중 바라보는 지점까지 라인트레이스를 쏘고, 그 거리를 기준으로 Depth of Field의 초점거리를 자동 보간하는 예제.

## 프로젝트 개요
- 엔진: Unreal Engine 5.6
- 입력: Enhanced Input (IMC_AutoFocus, IA_CameraRotation, IA_Zoom)
- 핵심 클래스: UInput, AAutoFocusPawn, AAutoFocusGameMode

## 핵심 기능
- 카메라 회전: 마우스 드래그(또는 매핑된 입력)로 Yaw/Pitch 제어
- 줌 토글: 줌 중에만 오토포커스 활성화
- 오토포커스: 카메라 전방으로 라인트레이스 → 히트 지점까지의 거리로 DoF 초점거리 보간
- 부드러운 전환: FOV/초점거리 모두 FInterpTo로 자연스럽게 변경

## 입력/조작
- 회전: IA_CameraRotation → FVector 값(X=Yaw, Y=Pitch)
- 줌: IA_Zoom → bool (눌림/뗌)
- 기본 FOV: 90, 줌 FOV: 45, 보간 속도: 3

## 동작 원리
1) 줌이 활성화되면 카메라 위치(Start)에서 전방(Forward)으로 일정 거리(기본 5000) 라인트레이스  
2) 첫 히트까지의 벡터 길이 = 목표 초점거리  
3) 현재 초점거리(FocusLocation)를 목표값으로 FInterpTo 보간  
4) 카메라 PostProcessSettings.DepthOfFieldFocalDistance에 적용

## 주요 클래스와 역할
- UInput (UObject)
  - /Game/IA/IMC_AutoFocus, /Game/IA/IA_CameraRotation, /Game/IA/IA_Zoom 에셋 로드
  - Context/Actions 보관용 CDO
- AAutoFocusPawn (APawn)
  - SpringArm + Camera 구성, 카메라 컨트롤 회전 사용
  - BeginPlay: LocalPlayer Subsystem에 MappingContext 추가
  - Tick: 줌 시 FOV/DoF 보간, 라인트레이스 및 초점거리 계산
  - SetupPlayerInputComponent: EnhancedInput로 액션 바인딩
- AAutoFocusGameMode
  - DefaultPawnClass = AAutoFocusPawn

## 주요 파라미터(AAutoFocusPawn)
- DefaultFOV = 90
- ZoomFOV = 45
- ZoomInterpSpeed = 3
- AutoFocusTraceDistance = 5000
- AutoFocusSpeed = 10

## 예시 이미지

<img width="1407" height="849" alt="이미지" src="https://github.com/user-attachments/assets/8e14244d-ce0e-48e8-879c-948fe2ded268" />
<img width="1410" height="850" alt="이미지 (1)" src="https://github.com/user-attachments/assets/7020f391-7331-4893-a3f5-d88d549720a1" />
