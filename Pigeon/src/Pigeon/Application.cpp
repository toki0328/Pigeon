#include "pgpch.h"
#include "Application.h"

#include "Pigeon/Events/ApplicationEvent.h"
#include "Pigeon/Log.h"

#include <GLFW/glfw3.h>

namespace Pigeon {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 1, 0, 1);

			// 用当前缓冲区清除值，GL_COLOR_BUFFER_BIT指清除颜色缓冲
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
