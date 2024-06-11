#pragma once

// 创建客户端应用程序

#ifdef PG_PLATFORM_WINDOWS

// exturn调用其他文件的变量
extern Pigeon::Application* Pigeon::CreateApplication();

void main()
{
	Pigeon::Log::Init();	// 记得在"Pigeon.h"中调用其头文件
	PG_CORE_WARN("Initialized log");
	int a = 5;
	PG_INFO("Hello Var={0}", a);
	PG_ERROR("error!");
	PG_CORE_CRITICAL("111");

	auto app = Pigeon::CreateApplication();
	app->Run();
	delete app;
}

#endif // PG_PLATFORM_WINDOWS
