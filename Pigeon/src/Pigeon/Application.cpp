#include "Application.h"

#include "Pigeon/Events/ApplicationEvent.h"
#include "Pigeon/Log.h"

namespace Pigeon {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent event(1280, 720);
		if (event.IsInCategory(EventCategoryApplication))
		{
			PG_TRACE(event.ToString());
		}
		if (event.IsInCategory(EventCategoryInput))
		{
			PG_TRACE(event.ToString());
		}
		

		while (true);	// 持续运行
	}
}
