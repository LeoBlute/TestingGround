#pragma once

namespace Application
{
	void Loop();
	void Start();
	void End();

	void SetPause(bool pause);
	void Pause();

	bool IsPaused();

	void Quit();
}