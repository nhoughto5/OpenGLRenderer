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
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["GLM"] = "vendor/glm"
IncludeDir["STB"] = "vendor/stb"
IncludeDir["VULKAN"] = "vendor/Vulkan/Include"
IncludeDir["TOL"] = "vendor/tinyobjloader"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["PugIXml"] = "vendor/pugixml/src"

group "Dependencies"
	include "vendor/GLFW"
	include "vendor/Glad"
	include "vendor/pugixml"

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
	
	prebuildcommands 
	{
		"RD /S /Q \"$(TargetDir)assets\\\""
	}
	
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
		"vendor/spdlog/include",
		"%{IncludeDir.PugIXml}"
	}
	libdirs  
	{ 
		"vendor/Vulkan/Lib"
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
		
project "OBJConverter"
	location "OBJConverter"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	pchheader "pch.h"
	pchsource "OBJConverter/src/pch.cpp"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.TOL}",
		"vendor/spdlog/include"
	}