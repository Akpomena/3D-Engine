workspace "3D Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["glfw"] = "vendor/glfw/include"
IncludeDir["glad"] = "vendor/glad/include"
IncludeDir["imgui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["stb_Image"] = "vendor/stb_Image"

include "premake/glfw.lua"
include "premake/glad.lua"
include "premake/imgui.lua"


-- Project file of 3D Engine

project "3D Engine"
	location "3D Engine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/assets/shaders/**",
		"%{prj.name}/src/**.cpp",
		"vendor/stb_Image/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_Image}"
	}

	defines
	{	
		"_CRT_SECURE_NO_WARNINGS"
	}

	links
	{
		"ImGui",
		"Glad",
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
