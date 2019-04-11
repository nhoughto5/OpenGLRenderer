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
IncludeDir["GLFW"] = "RenderPlayground/ExternalResources/GLFW/include"
IncludeDir["GLM"] = "RenderPlayground/ExternalResources/glm"
IncludeDir["STB"] = "RenderPlayground/ExternalResources/stb"
IncludeDir["VULKAN"] = "RenderPlayground/ExternalResources/Vulkan/Include"
IncludeDir["TOL"] = "RenderPlayground/ExternalResources/tinyobjloader"
IncludeDir["Glad"] = "RenderPlayground/ExternalResources/Glad/include"

group "Dependencies"
	include "RenderPlayground/ExternalResources/Glad"

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
		"RenderPlayground/ExternalResources/Vulkan/Lib",
		"RenderPlayground/ExternalResources/GLFW/lib-vc2015"
	}
	links
	{
		"vulkan-1.lib",
		"Glad",
		"glfw3.lib",
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