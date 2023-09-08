
#pragma once

namespace Window {
	bool Init();
	void Terminate();
	void MakeContextCurrent();
	void ClearScreen();
	void ProcessInputs();
	void SwapBuffers();

	#pragma region Getters
	void* GetRawWindow();
	int GetWidth();
	int GetHeight();
	int GetXPos();
	int GetYPos();
	#pragma endregion

	#pragma region Setters
	void SetSize(float width, float height);
	#pragma endregion


}