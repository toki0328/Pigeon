#pragma once

// 引擎端

#include "Core.h"
#include "Events/Event.h"

namespace Pigeon {

	// 在Sanbox中使用此类，链接过去
	class PIGEON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// 在客户端定义创建，用于返回一个app的对象
	Application* CreateApplication();
}


