workspace "RenderPlayground"
	architecture "x64"
	startproject "RenderPlayground"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "RenderPlayground/vendor/GLFW/include"
IncludeDir["GLM"] = "RenderPlayground/vendor/glm"
IncludeDir["STB"] = "RenderPlayground/vendor/stb"
IncludeDir["VULKAN"] = "RenderPlayground/vendor/Vulkan/Include"
IncludeDir["TOL"] = "RenderPlayground/vendor/tinyobjloader"
IncludeDir["Glad"] = "RenderPlayground/vendor/Glad/include"

group "Dependencies"
	include "RenderPlayground/vendor/GLFW"
	include "RenderPlayground/vendor/Glad"

group ""
project "RenderPlayground"
	location "RenderPlayground"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	pchheader "pch.h"
	pchsource "RenderPlayground/src/pch.cpp"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.VULKAN}",
		"%{IncludeDir.TOL}"
	}
	libdirs  
	{ 
		"RenderPlayground/vendor/Vulkan/Lib"
	}
	links
	{
		"vulkan-1.lib",
		"Glad",
		"GLFW",
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines
		{
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "NVR_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NVR_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NVR_DIST"
		runtime "Release"
		optimize "On"