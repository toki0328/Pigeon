#pragma once

// 引擎端

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Pigeon/Events/ApplicationEvent.h"
#include "Pigeon/LayerStack.h"

namespace Pigeon {

	// 在Sanbox中使用此类，链接过去
	class PIGEON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window; // 创建唯一指针，保存Window的一个实例
		bool m_Running = true;
		LayerStack m_LayerStack;	// 在栈上创建，继承Application的生命周期

	private:
		static Application* s_Instance;
	};

	// 在客户端定义创建，用于返回一个app的对象
	Application* CreateApplication();
}


