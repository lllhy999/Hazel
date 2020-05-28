#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	
extern Hazel::Application* Hazel::CreateApplication();

int main()
{
	//printf("Hazel Game Engine!");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif