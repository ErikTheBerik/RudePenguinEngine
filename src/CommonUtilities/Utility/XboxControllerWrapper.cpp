#include "XboxControllerWrapper.h"

int XboxControllerWrapper::ourControllerIndex = -1;

XboxControllerWrapper::XboxControllerWrapper()
{
	ourControllerIndex += 1;
	myControllerIndex = ourControllerIndex;

	for (int i = 0; i < ButtonCount; ++i)
	{
		myPreviousButtonStates[i] = false;
		myButtonState[i] = false;
		myGamepadButtonsPressed[i] = false;
	}

	myShouldVibrate = false;
	myRightMotorVibration = 0.f;
	myLeftMotorVibration = 0.f;
	myShouldStopVibrate = 0.f;
	myShouldStopVibrate = true;
	//Vibrate(0.f, 0.f);
}


XboxControllerWrapper::~XboxControllerWrapper()
{
	ourControllerIndex -= 1;
}

void XboxControllerWrapper::Update()
{
	//if (IsConnected() == true)
	//{
	//	for (int i = 0; i < ButtonCount; ++i)
	//	{
	//		myButtonState[i] = (myInputState.Gamepad.wButtons & XINPUT_Buttons[i]) == XINPUT_Buttons[i];
	//		myGamepadButtonsPressed[i] = !myPreviousButtonStates[i] && myButtonState[i];
	//	}
	//}

	myPreviousState = myInputState;
	myInputState = GetInputState();

	/*if (myShouldVibrate)
	{
		XINPUT_VIBRATION vibrationState;
		ZeroMemory(&vibrationState, sizeof(XINPUT_VIBRATION));
		int leftMotor = static_cast<int>(myLeftMotorVibration * 65535.0f);
		int rightMotor = static_cast<int>(myRightMotorVibration * 65535.0f);

		vibrationState.wLeftMotorSpeed = static_cast<WORD>(leftMotor);
		vibrationState.wRightMotorSpeed = static_cast<WORD>(rightMotor);

		XInputSetState(myControllerIndex, &vibrationState);
		if (myShouldStopVibrate)
		{
			myShouldVibrate = false;
			myShouldStopVibrate = false;
		}
	}*/

}

XINPUT_STATE XboxControllerWrapper::GetInputState()
{
	ZeroMemory(&myInputState, sizeof(XINPUT_STATE));
	XInputGetState(myControllerIndex, &myInputState);

	return myInputState;
}

bool XboxControllerWrapper::IsConnected()
{
	//return true;
	ZeroMemory(&myInputState, sizeof(XINPUT_STATE));
	DWORD result = XInputGetState(myControllerIndex, &myInputState);
	if (result == ERROR_SUCCESS)
	{
		return true;
	}
	return false;
}

const glm::vec2 XboxControllerWrapper::GetLeftThumbStickDirection()
{
	float LX = myInputState.Gamepad.sThumbLX;
	float LY = myInputState.Gamepad.sThumbLY;

	float magnitude = static_cast<float>(sqrt(LX*LX + LY*LY));

	if (magnitude == 0)
	{
		return glm::vec2(0.0f, 0.0f);
	}

	float normalizedLX = LX / magnitude;
	float normalizedLY = LY / magnitude;

	float normalizedMagnitude = 0;

	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		if (magnitude > 32767)
		{
			magnitude = 32767;
		}

		magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

		normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	}
	else
	{
		magnitude = 0.f;
		normalizedMagnitude = 0.f;
	}


	return glm::vec2(normalizedLX, normalizedLY) * normalizedMagnitude;
}

bool XboxControllerWrapper::GetButtonPressed(eXboxButtons aButton)
{
	if ((myPreviousState.Gamepad.wButtons & XINPUT_Buttons[(int)aButton]) == 0 &&
		(myInputState.Gamepad.wButtons & XINPUT_Buttons[(int)aButton]) > 0)
	{
		return true;
	}
	return false;
	//return myGamepadButtonsPressed[static_cast<int>(aButton)];
}

bool XboxControllerWrapper::GetButtonPressed(int aButton)
{
	if ((myPreviousState.Gamepad.wButtons & aButton) == 0 &&
		(myInputState.Gamepad.wButtons & aButton) > 0)
	{
		return true;
	}
	return false;
	//return myGamepadButtonsPressed[static_cast<int>(aButton)];
}

bool XboxControllerWrapper::GetButtonDown(eXboxButtons aButton)
{
	if ((myInputState.Gamepad.wButtons & XINPUT_Buttons[(int)aButton]) > 0)
	{
		return true;
	}
	/*if (myInputState.Gamepad.wButtons & XINPUT_Buttons[static_cast<int>(aButton)])
	{
		return true;
	}*/
	return false;
}

bool XboxControllerWrapper::GetButtonReleased(eXboxButtons aButton)
{
	if ((myInputState.Gamepad.wButtons & XINPUT_Buttons[(int)aButton]) == 0 &&
		(myPreviousState.Gamepad.wButtons & XINPUT_Buttons[(int)aButton]) > 0)
	{
		return true;
	}
	/*if (GetButtonDown(aButton) == false && myPreviousButtonStates[static_cast<int>(aButton)] == true)
	{
		return true;
	}*/
	return false;
}

//void XboxControllerWrapper::RefreshState()
//{
//	memcpy(myPreviousButtonStates, myButtonState, sizeof(myPreviousButtonStates));
//}

void XboxControllerWrapper::Vibrate(float aLeftMotor, float aRightMotor)
{
	/*myShouldVibrate = true;
	myLeftMotorVibration = aLeftMotor;
	myRightMotorVibration = aRightMotor;*/
	XINPUT_VIBRATION vibrationState;
	ZeroMemory(&vibrationState, sizeof(XINPUT_VIBRATION));
	int leftMotor = static_cast<int>(aLeftMotor * 65535.0f);
	int rightMotor = static_cast<int>(aRightMotor * 65535.0f);

	vibrationState.wLeftMotorSpeed = static_cast<WORD>(leftMotor);
	vibrationState.wRightMotorSpeed = static_cast<WORD>(rightMotor);

	XInputSetState(myControllerIndex, &vibrationState);
}

std::vector<eXboxButtons> XboxControllerWrapper::GetButtonsPressed()
{
	std::vector<eXboxButtons> buttons;
	for (int i = 0; i < static_cast<int>(eXboxButtons::Length); ++i)
	{
		if (GetButtonPressed(static_cast<eXboxButtons>(i)) == true)
		{
			buttons.push_back(static_cast<eXboxButtons>(i));
		}
	}
	return buttons;
}

std::vector<eXboxButtons> XboxControllerWrapper::GetButtonsDown()
{
	std::vector<eXboxButtons> buttons;
	for (int i = 0; i < static_cast<int>(eXboxButtons::Length); ++i)
	{
		if (GetButtonDown(static_cast<eXboxButtons>(i)) == true)
		{
			buttons.push_back(static_cast<eXboxButtons>(i));
		}
	}
	return buttons;
}

std::vector<eXboxButtons> XboxControllerWrapper::GetButtonsReleased()
{
	std::vector<eXboxButtons> buttons;
	for (int i = 0; i < static_cast<int>(eXboxButtons::Length); ++i)
	{
		if (GetButtonReleased(static_cast<eXboxButtons>(i)) == true)
		{
			buttons.push_back(static_cast<eXboxButtons>(i));
		}
	}
	return buttons;
}

float XboxControllerWrapper::GetRightTriggerDownAmount()
{
	return static_cast<float>(myInputState.Gamepad.bRightTrigger) / 255.f;
}

float XboxControllerWrapper::GetLeftTriggerDownAmount()
{
	return static_cast<float>(myInputState.Gamepad.bLeftTrigger) / 255.f;
}

void XboxControllerWrapper::SetControllerNumber(const int aControllerNumber)
{
	myControllerIndex = aControllerNumber;
}

int XboxControllerWrapper::GetControllerNumber() const
{
	return myControllerIndex;
}

void XboxControllerWrapper::StopVibrate()
{
	Vibrate(0.f, 0.f);
}

const glm::vec2 XboxControllerWrapper::GetRightThumbStickDirection()
{
	float RX = static_cast<float>(myInputState.Gamepad.sThumbRX);
	float RY = static_cast<float>(myInputState.Gamepad.sThumbRY);

	float magnitude = static_cast<float>(sqrt(RX*RX + RY*RY));

	float normalizedRX = RX / magnitude;
	float normalizedRY = RY / magnitude;

	float normalizedMagnitude = 0;

	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		if (magnitude > 32767)
		{
			magnitude = 32767;
		}

		magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

		normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	}
	else
	{
		magnitude = 0.f;
		normalizedMagnitude = 0.f;
	}


	return glm::vec2(normalizedRX, normalizedRY) * normalizedMagnitude;
}