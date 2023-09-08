#pragma once

#define GUI_VAR_DEF(TYPE_NAMING, TYPE)\
TYPE Get##TYPE_NAMING(const char* name);\
void Set##TYPE_NAMING(const char* name, TYPE value);\
void Erase##TYPE_NAMING(const char* name);

#define GUI_VAR_INPUT_DEF(TYPE_NAMING)\
void Set##TYPE_NAMING##InputStats(const char* name, const InputStats& stats);

namespace Graphics {
	struct Color
	{
		float r, g, b, a;
	};
	enum ColorStyle{
		Classic,
		Dark,
		Light
	};

	void SetColorStyle(ColorStyle style);
	bool Init();
	void Terminate();
	void NewFrame();
	void Render();

	namespace Console
	{
		enum InputType
		{
			Default = 0,
			Drag = 1,
			Slider = 2
		};
		struct InputStats {
			InputType currentType = InputType::Default;
			float min = 0.0f;
			float max = 0.0f;
			float speed = 1.0f;
		};
		//Gets,by name,if the button has been pressed or
		//creates the button if it has not been created
		bool IsButtonPressed(const char* name);
		void EraseButton(const char* name);

		GUI_VAR_DEF(Boolean, bool);
		GUI_VAR_DEF(String, std::string);
		GUI_VAR_DEF(Float, float);
		GUI_VAR_DEF(Double, double);
		GUI_VAR_DEF(Integer, int);

		GUI_VAR_INPUT_DEF(Float);
		GUI_VAR_INPUT_DEF(Integer);

		//Setup console to work,call it between NewFrame and Render
		void PushToRender();
		void LogMessage(const char* msg, const Color& color);
	}
}

typedef Graphics::Console::InputStats InputStats;
typedef Graphics::Console::InputType InputType;