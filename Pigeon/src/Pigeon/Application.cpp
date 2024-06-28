#include "pgpch.h"
#include "Application.h"

#include "Pigeon/Log.h"

#include <GLFW/glfw3.h>

/*
* std::bind
* 函数适配器，接受一个可调用对象（callable object），生成一个新的可调用对象来“适应”原对象的参数列表
* 可绑定参数和原函数，要绑定引用参数时，得用ref()
* 当需要引用的方式把参数传递给模板函数时，利用ref(), ref()能用包装类型reference_wrapper来代替原本会被识别的值类型，而reference_wrapper能隐式转换为被引用的值的引用类型
*/
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Pigeon {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		PG_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//PG_CORE_TRACE("{0}", e.ToString());

		// 向后迭代
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0, 0, 0, 1);

			// 用当前缓冲区清除值，GL_COLOR_BUFFER_BIT指清除颜色缓冲
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
