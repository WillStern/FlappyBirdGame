#pragma once

#include "GLFW/glfw3.h"


class Mouse {

public:
	static void MousePosCallback(GLFWwindow* window, double _x, double _y);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	static double GetMouseX();
	static double GetMouseY();
	
	static bool ButtonDown(int button);
	static bool ButtonUp(int button);
	static bool Button(int button);


private:
	static double x;
	static double y;

	static bool buttons[]; //button currently pushed down
	static bool buttonsDown[]; //just pressed
	static bool buttonsUp[]; //just released
	

};