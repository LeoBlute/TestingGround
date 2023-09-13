#include "pch.hpp"
#include "Graphics.hpp"
#include "Debug.hpp"
#include "Time.hpp"

#define DEBUG_VAR_IMP(TYPE_NAMING, TYPE)\
TYPE Debug::Get##TYPE_NAMING##(const char* name)\
{\
	return Graphics::Console::Get##TYPE_NAMING##(name);\
}\
void Debug::Set##TYPE_NAMING##(const char* name, TYPE value)\
{\
	Graphics::Console::Set##TYPE_NAMING##(name, value);\
}\
void Debug::Erase##TYPE_NAMING##(const char* name)\
{\
	Graphics::Console::Erase##TYPE_NAMING##(name);\
}

#define DEBUG_VAR_INPUT_IMP(TYPE_NAMING)\
void Debug::Set##TYPE_NAMING##InputStats\
(const char* name, Graphics::Console::InputStats& stats)\
{\
	Graphics::Console::Set##TYPE_NAMING##InputStats(name, stats);\
}\

void Debug::Log(const std::string& msg, float r, float g, float b, float a)
{
	Graphics::Color color{r, g, b, a};
	std::string fmsg = Time::GetCurrentDateAndTime();
	fmsg.append("-");
	fmsg.append(msg);
	Graphics::Console::LogMessage(fmsg.c_str(), color);
}

DEBUG_VAR_IMP(Boolean, bool);
DEBUG_VAR_IMP(String, std::string);
DEBUG_VAR_IMP(Float, float);
DEBUG_VAR_IMP(Double, double);
DEBUG_VAR_IMP(Integer, int);

DEBUG_VAR_INPUT_IMP(Float);
DEBUG_VAR_INPUT_IMP(Integer);

void Debug::ClearLogger()
{
	Graphics::Console::ClearLogger();
}

void Debug::ClearConsole()
{
	Graphics::Console::ClearConsole();
}
