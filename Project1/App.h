#pragma once
#include "Window.h"
#include "Timer.h"
#include "Box.h"
#include<memory>
#include "ImguiManger.h"
#include "Camera.h"
#include "PointLight.h"

class App
{
	
public:
	App();
	int Go();
private:
	void DoFrame();
	void ImguiStuff();
private:
	float speed_factor = 1.0f;
	ImguiManager imgui;
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<class Drawable>> boxes;
	Camera cam;
	PointLight light;
};