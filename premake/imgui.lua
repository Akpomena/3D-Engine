	-- Project file for Imgui

    project "ImGui"
	location "../vendor/imgui"
	kind "StaticLib"
	language "C++"
    cppdialect "C++20"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
	   "../vendor/imgui/imconfig.h",
       "../vendor/imgui/imgui.cpp",
       "../vendor/imgui/imgui.h",
       "../vendor/imgui/imgui_demo.cpp",
       "../vendor/imgui/imgui_draw.cpp",
       "../vendor/imgui/imgui_internal.h",
       "../vendor/imgui/imgui_tables.cpp",
       "../vendor/imgui/imgui_widgets.cpp",
       "../vendor/imgui/imstb_rectpack.h",
       "../vendor/imgui/imstb_textedit.h",
       "../vendor/imgui/imstb_truetype.h"
	}    

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

