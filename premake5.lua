workspace "Pigeon"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Pigeon"
	location "Pigeon"
	kind "SharedLib"
	language "C++"

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
		"%{prj.name}/vendor/spdlog/spdlog-1.14.1-win64/include"
	}

	-- 指定库目录
	libdirs 
	{
		"%{prj.name}/vendor/spdlog/spdlog-1.14.1-win64/lib"
	}

	-- 指定要链接的库
	links
	{
		"spdlogd.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PG_BUILD_DLL",
			"PG_PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "PG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PG_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PG_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PG_DIST"
		optimize "On"