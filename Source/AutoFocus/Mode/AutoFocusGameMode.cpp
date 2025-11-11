
#include "AutoFocusGameMode.h"

#include "AutoFocus/Pawn/AutoFocusPawn.h"

AAutoFocusGameMode::AAutoFocusGameMode()
{
	DefaultPawnClass = AAutoFocusPawn::StaticClass();
}
