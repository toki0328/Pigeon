workspace "Pigeon"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

startproject  "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory)
-- 目录列表
IncludeDir = {}
IncludeDir["GLFW"] = "Pigeon/vendor/GLFW/include"
IncludeDir["Glad"] = "Pigeon/vendor/Glad/include"
IncludeDir["ImGui"] = "Pigeon/vendor/imgui"

-- 包含GLFW的premake的目录，相当于c++的头文件
include "Pigeon/vendor/GLFW"
include "Pigeon/vendor/Glad"
include "Pigeon/vendor/imgui"



project "Pigeon"
	location "Pigeon"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- 预编译头文件
	pchheader "pgpch.h"
	pchsource "Pigeon/src/pgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/spdlog-1.14.1-win64/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	-- 指定库目录
	libdirs 
	{
		"%{prj.name}/vendor/spdlog/spdlog-1.14.1-win64/lib",
	}

	-- 指定要链接的库
	links
	{
		"spdlogd.lib",
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PG_BUILD_DLL",
			"PG_PLATFORM_WINDOWS"
			--"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "PG_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "PG_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "PG_DIST"
		optimize "On"
		runtime "Release"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Pigeon/vendor/spdlog/spdlog-1.14.1-win64/include",
		"Pigeon/src"
	}

	libdirs 
	{
		"Pigeon/vendor/spdlog/spdlog-1.14.1-win64/lib"
	}

	links
	{
		"Pigeon",
		"spdlogd.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PG_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "PG_RELEASE"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "PG_DIST"
		optimize "On"
		runtime "Release"