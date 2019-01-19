#pragma once
#include <windows.h>
#include <Xinput.h>
#include "../glm/vec2.hpp"
#include <vector>
#pragma comment (lib, "XInput9_1_0.lib")
#pragma comment (lib, "XInput.lib")



static const WORD XINPUT_Buttons[] =
{
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK

};

enum class eXboxButtons
{
	A,
	B,
	X,
	Y,
	DPadUp,
	DPadDown,
	DPadLeft,
	DPadRight,
	LeftShoulder,
	RightShoulder,
	LeftThumb,
	RightThumb,
	Start,
	Back,
	Length
};

class XboxControllerWrapper
{
public:
	XboxControllerWrapper();
	~XboxControllerWrapper();

	void Update();
	XINPUT_STATE GetInputState();
	bool IsConnected();
	const glm::vec2 GetRightThumbStickDirection();
	const glm::vec2 GetLeftThumbStickDirection();
	bool GetButtonPressed(eXboxButtons aButton);
	bool GetButtonPressed(int aButton);

	bool GetButtonDown(eXboxButtons aButton);
	bool GetButtonReleased(eXboxButtons aButton);
	void Vibrate(float aLeftMotor, float aRightMotor);
	std::vector<eXboxButtons> GetButtonsPressed();
	std::vector<eXboxButtons> GetButtonsDown();
	std::vector<eXboxButtons> GetButtonsReleased();
	float GetRightTriggerDownAmount();
	float GetLeftTriggerDownAmount();
	void SetControllerNumber(const int aControllerNumber);
	int GetControllerNumber() const;
	void StopVibrate();
private:
	XINPUT_STATE myInputState;
	XINPUT_STATE myPreviousState;
	static int ourControllerIndex;
	static const int ButtonCount = 14;
	int myControllerIndex;
	float myRightTrigger;
	float myLeftTrigger;

	float myRightMotorVibration;
	float myLeftMotorVibration;



	bool myShouldVibrate;
	bool myShouldStopVibrate;

	bool myPreviousButtonStates[ButtonCount];
	bool myButtonState[ButtonCount];
	bool myGamepadButtonsPressed[ButtonCount];
};

