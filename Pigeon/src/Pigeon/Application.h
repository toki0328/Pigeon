#pragma once

// 引擎端

#include "Core.h"

namespace Pigeon {

	// 在Sanbox中使用此类，链接过去
	class PIGEON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// 在客户端定义创建
	Application* CreateApplication();
}


