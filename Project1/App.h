#pragma once
#include "Window.h"
#include "Timer.h"
#include <memory>
#include "ImguiManger.h"
#include "Camera.h"
#include "PointLight.h"
#include "Mesh.h"
#include "TestCube.h"
class App
{
	
public:
	App();
	int Go();
private:
	void DoFrame();
	void ImguiStuff();
private:
	int x=0, y=0;
	float speed_factor = 1.0f;
	ImguiManager imgui;
	Window wnd;
	Timer timer;
	Camera cam;
	PointLight light;
	MODEL_DESC hammer_time_desc =
	{
		1.0f,
		"Models\\Rune_Hammer\\Rune_Hammer.obj",
		"Models\\Rune_Hammer\\Textures\\Rune_Hammer_Albedo.png",
		"Models\\Rune_Hammer\\Textures\\Rune_Hammer_Normal.png",
		"Models\\Rune_Hammer\\Textures\\Rune_Hammer_Metallic.png",
		"Models\\Rune_Hammer\\Textures\\Rune_Hammer_Emission.png",
	};
	Model hammer_time{ wnd.Gfx(),hammer_time_desc };

	//MODEL_DESC plank_desc =
	//{
	//	1.0f,
	//	"Models\\Plank\\Plank.obj",
	//	"Models\\Plank\\Textures\\Planks_albedo_2k.png",
	//	"Models\\Plank\\Textures\\Planks_normal_2k.png",
	//	"-1",
	//	"-1",
	//};
	//Model plank{ wnd.Gfx(),plank_desc };

	TestCube cube{ wnd.Gfx(),4.0f };

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