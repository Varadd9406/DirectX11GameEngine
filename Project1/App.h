#pragma once
#include "Window.h"
#include "Timer.h"
#include<memory>
#include "ImguiManger.h"
#include "Camera.h"
#include "PointLight.h"
#include "Mesh.h"
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
	Camera cam;
	PointLight light;
	Model AWP{ wnd.Gfx(),"Models\\Rune_Hammer\\Rune_Hammer.fbx" };
	struct
	{
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	} pos;
};