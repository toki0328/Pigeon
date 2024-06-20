#pragma once

// 创建客户端应用程序

// Windows系统
#ifdef PG_PLATFORM_WINDOWS

// exturn调用其他文件的变量
extern Pigeon::Application* Pigeon::CreateApplication();

void main()
{
	Pigeon::Log::Init();	// 记得在"Pigeon.h"中调用其头文件
	PG_CORE_INFO("Initialized log");

	// 创建的一个客户端应用实例
	auto app = Pigeon::CreateApplication();
	app->Run();
	delete app;
}

#endif // PG_PLATFORM_WINDOWS
