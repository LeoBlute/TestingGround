'# TestingGround

TestingGround is a framework application meant for quick debugging and nothing else<br />
<br />
The frameworkd includes:<br />
-Window System(glfw implementation)<br />
-Graphics System(ImGui implementation)<br />
-Error Catching<br />
-Logger for logging messages<br />
-Console for quick debug with buttons and variables<br />
-Pause/Unpause feature<br />
<br />
To use the framework got to TestingGround.cpp and write what you want to debug in<br />
Application::Start or Application::Loop or,in case a deletion is needed,Application::End<br />
<br />
Example code:<br />
```
void Application::Start()
{
	//Works similar to printf or std::cout,but it will only print/log to the Logger
	//Each Loggin Method has different color and different use cases
	Debug::Info("Application started");
	//Debug::Warning("Application Warning");
	//Debug::Error("Application Error!");

	//Create a float,a integer and a boolean with following names
	Debug::GetFloat("Float");
	Debug::GetInteger("Integer");
	//Boolean will be created with true as default
	Debug::SetBoolean("Boolean", true);

	//Set a slider functionality for the "Float" variable
	InputStats float_stats;
	float_stats.currentType = InputType::Slider;
	float_stats.min = -10.0f;
	float_stats.max = 10.0f;
	Debug::SetFloatInputStats("Float", float_stats);

	//Set a drag functionality for the "Integer" variable
	InputStats integer_stats;
	integer_stats.currentType = InputType::Drag;
	integer_stats.speed = 0.1f;
	Debug::SetIntegerInputStats("Integer", integer_stats);

	//All variables can be erased if desired
	//Debug::EraseFloat("Float");
	//Debug::EraseInteger("Integer");
	//Debug::EraseBoolean("Boolean");
}
```