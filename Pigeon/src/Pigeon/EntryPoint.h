#pragma once

// 创建客户端应用程序

#ifdef PG_PLATFORM_WINDOWS

// exturn调用其他文件的变量
extern Pigeon::Application* Pigeon::CreateApplication();

void main()
{
	auto app = Pigeon::CreateApplication();
	app->Run();
	delete app;
}

#endif // PG_PLATFORM_WINDOWS
