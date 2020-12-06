workspace "OpenGLRenderer"
	architecture "x64"
	startproject "OpenGLRenderer"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "OpenGLRenderer/vendor/GLFW/include"
IncludeDir["GLM"] = "OpenGLRenderer/vendor/glm"
IncludeDir["STB"] = "OpenGLRenderer/vendor/stb"
IncludeDir["VULKAN"] = "OpenGLRenderer/vendor/Vulkan/Include"
IncludeDir["TOL"] = "OpenGLRenderer/vendor/tinyobjloader"
IncludeDir["Glad"] = "OpenGLRenderer/vendor/Glad/include"
IncludeDir["PugIXml"] = "OpenGLRenderer/vendor/pugixml/src"

group "Dependencies"
	include "OpenGLRenderer/vendor/GLFW"
	include "OpenGLRenderer/vendor/Glad"
	include "OpenGLRenderer/vendor/pugixml"

group ""
project "OpenGLRenderer"
	location "OpenGLRenderer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	pchheader "pch.h"
	pchsource "OpenGLRenderer/src/pch.cpp"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	postbuildcommands 
	{
	  "XCOPY \"$(SolutionDir)$(ProjectName)\\assets\" \"$(TargetDir)\\assets\\\" /S"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"OGLR_ENABLE_ASSERTS"
	}
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.VULKAN}",
		"%{IncludeDir.TOL}",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.PugIXml}"
	}
	libdirs  
	{ 
		"OpenGLRenderer/vendor/Vulkan/Lib"
	}
	links
	{
		"Glad",
		"GLFW",
		"opengl32.lib",
		"pugixml"
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