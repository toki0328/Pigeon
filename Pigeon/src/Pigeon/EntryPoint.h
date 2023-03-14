#pragma once


#ifdef PG_PLATFORM_WINDOWS

extern Pigeon::Application* Pigeon::CreateApplication();	//客户端实现，在Application.h中定义

int main(int argc, char** argv)
{
	auto app = Pigeon::CreateApplication();	//创建应用程序
	app->Run();
	delete app;
}

#endif