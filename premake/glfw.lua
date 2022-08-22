project "GLFW"
    location "../vendor/glfw"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"../vendor/glfw/include/GLFW/glfw3.h",
		"../vendor/glfw/include/GLFW/glfw3native.h",
		"../vendor/glfw/src/glfw_config.h",
		"../vendor/glfw/src/context.c",
		"../vendor/glfw/src/init.c",
		"../vendor/glfw/src/input.c",
		"../vendor/glfw/src/monitor.c",
        "../vendor/glfw/src/platform.c",
		"../vendor/glfw/src/vulkan.c",
		"../vendor/glfw/src/window.c",
        "../vendor/glfw/src/null_platform.h",
        "../vendor/glfw/src/null_joystick.h",
        "../vendor/glfw/src/null_init.c",
    
        "../vendor/glfw/src/null_monitor.c",
        "../vendor/glfw/src/null_window.c",
        "../vendor/glfw/src/null_joystick.c",

        "../vendor/glfw/src/win32_module.c",
        "../vendor/glfw/src/win32_init.c",
        "../vendor/glfw/src/win32_joystick.c",
        "../vendor/glfw/src/win32_monitor.c",
        "../vendor/glfw/src/win32_time.c",
        "../vendor/glfw/src/win32_thread.c",
        "../vendor/glfw/src/win32_window.c",
        "../vendor/glfw/src/wgl_context.c",
        "../vendor/glfw/src/egl_context.c",
        "../vendor/glfw/src/osmesa_context.c"
	}

    defines 
    { 
        "_GLFW_WIN32",
        "_CRT_SECURE_NO_WARNINGS"
    }

    
	filter "system:windows"
        systemversion "latest"


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
