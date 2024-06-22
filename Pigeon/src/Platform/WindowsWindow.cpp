#include "pgpch.h"
#include "WindowsWindow.h"

#include "Pigeon/Events/ApplicationEvent.h"
#include "Pigeon/Events/KeyEvent.h"
#include "Pigeon/Events/MouseEvent.h"

//#include <glad/glad.h>	// glad.h必须在glfw3.h前调用
//#include <GLFW/glfw3.h>

namespace Pigeon {

	static bool s_GLFWInitialized = false;

	// 错误回调
	static void GLFWErrorCallback(int error_code, const char* description)
	{
		PG_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		PG_CORE_INFO("Creating window {0} ({1} {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			PG_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		// 初始化GLFW
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		// 初始化Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PG_CORE_ASSERT(status, "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);	// 设置指定窗口的用户定义指针。当前值保留直到窗口被销毁
		SetVSync(true);

		// 设置GLFW回调
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}

					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		/* <关于GLFW事件的处理>
		* GLFW需要定期地与窗口系统进行交流，不仅是为了接收事件，还是为了让整个应用看起来没有卡住。当你有着可见的窗口时，事件处理必须定期执行，正常情况下它会在每帧的缓冲区交换之后进行
		* 这里有两种方式来处理挂起的事件。轮询（polling）和等待（waiting)，即glfwPollEvents()和glfwWaitEvent()
		* 
		* glwWaitEvents()
		* 当连续渲染时这是最好的选择，像大多数的游戏那样。如果你只需要在收到新的输入后更新一次渲染，glfwWaitEvents 会是更好的选择。
		* 它会一直等待直到收到至少一个事件，与此同时它会将线程进入休眠状态， 然后处理所有收到的事件。这将会节省大量的CPU周期，比如对于一些修改器界面来说是非常有用的
		*/

		/* <关于GLFW交换缓冲>
		* GLFW默认使用双缓冲技术
		*/

		// 轮询事件、交换缓冲区
		glfwSwapBuffers(m_Window);
		glfwPollEvents();	
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			// 等待1帧被调用
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		// 跟踪是否被启用
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}