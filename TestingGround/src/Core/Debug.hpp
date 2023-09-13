#pragma once

namespace Graphics {
	namespace Console {
		struct InputStats;
	}
}

namespace Debug {
	#pragma region Logging
	void Log(const std::string& msg, float r, float g, float b, float a);
	template<typename T>
	constexpr static inline void AddToStream(std::ostringstream& stream, const T& arg) {
		stream << arg;
	}

	template<typename T, typename... Args>
	constexpr static inline void AddToStream(std::ostringstream& stream, const T& arg, const Args&... args) {
		stream << arg;
		AddToStream(stream, args...);
	}
	template<typename... Args>
	inline void Warning(Args... args)
	{
		std::ostringstream stream;
		stream << "Warning:";
		AddToStream(stream, args...);
		const std::string strmsg = stream.str();
		const char* fmsg = strmsg.c_str();
		Log(fmsg, 1.0f, 0.8f, 0.0f, 1.0f);
	}
	template<typename... Args>
	inline void Error(Args... args)
	{
		std::ostringstream stream;
		stream << "Error:";
		AddToStream(stream, args...);
		const std::string strmsg = stream.str();
		const char* fmsg = strmsg.c_str();
		Log(fmsg, 1.0f, 0.0f, 0.0f, 1.0f);
	}
	template<typename... Args>
	inline void Info(Args... args)
	{
		std::ostringstream stream;
		stream << "Info:";
		AddToStream(stream, args...);
		const std::string strmsg = stream.str();
		const char* fmsg = strmsg.c_str();
		Log(fmsg, 1.0f, 1.0f, 1.0f, 1.0f);
	}
	#pragma endregion

	#pragma region Console
	#define DEBUG_VAR_DEF(TYPE_NAMING, TYPE)\
	TYPE Get##TYPE_NAMING(const char* name);\
	void Set##TYPE_NAMING(const char* name, TYPE value);\
	void Erase##TYPE_NAMING(const char* name);

	#define DEBUG_VAR_INPUT_DEF(TYPE_NAMING)\
	void Set##TYPE_NAMING##InputStats\
	(const char* name, Graphics::Console::InputStats& stats);

	DEBUG_VAR_DEF(Boolean, bool);
	DEBUG_VAR_DEF(String, std::string);
	DEBUG_VAR_DEF(Float, float);
	DEBUG_VAR_DEF(Double, double);
	DEBUG_VAR_DEF(Integer, int);

	DEBUG_VAR_INPUT_DEF(Float);
	DEBUG_VAR_INPUT_DEF(Integer);

	void ClearLogger();
	void ClearConsole();
	#pragma endregion
}