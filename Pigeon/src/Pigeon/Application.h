#pragma once

// 引擎端

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Pigeon/Events/ApplicationEvent.h"

namespace Pigeon {

	// 在Sanbox中使用此类，链接过去
	class PIGEON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window; // 创建唯一指针，保存Window的一个实例
		bool m_Running = true;

	};

	// 在客户端定义创建，用于返回一个app的对象
	Application* CreateApplication();
}


