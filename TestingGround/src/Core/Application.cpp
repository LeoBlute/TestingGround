#include "pch.hpp"
#include "Application.hpp"

inline bool isPaused;

void Application::SetPause(bool pause)
{
	isPaused = pause;
}

void Application::Pause()
{
	SetPause(true);
}

bool Application::IsPaused()
{
	return isPaused;
}