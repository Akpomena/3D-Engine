project "Glad"
    location "../vendor/glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("../../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"../vendor/glad/src/glad.c",
		"../vendor/glad/include/glad/glad.h",
		"../vendor/glad/include/KHR/khrplatform.h"
	}

	includedirs
	{
		"../vendor/glad/include"
	}


	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
