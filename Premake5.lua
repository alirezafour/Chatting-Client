-- premake 5
workspace "Four"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Development",
        "Shipping"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Four/vendor/GLFW/include"
IncludeDir["Glad"] = "Four/vendor/Glad/include"
IncludeDir["ImGui"] = "Four/vendor/imgui"
IncludeDir["glm"] = "Four/vendor/glm"

group "Dependecies"
    include "Four/vendor/GLFW" -- Adding glfw premake
    include "Four/vendor/Glad" -- Adding glad premake
    include "Four/vendor/imgui"

group ""

project "Four"
    location "Four"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-Intermediate/" .. outputdir .. "/%{prj.name}")

    --pre Header
    pchheader "fourpch.h" 
    pchsource "Four/src/fourpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"

    }

	links -- link static libs
	{ 
		"GLFW",
		"Glad",
        "ImGui",
		"opengl32.lib"
	}

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "FOUR_PLATFORM_WINDOWS",
            "FOUR_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "USING_GLFW"
        }

        filter "configurations:Debug"
            defines "FOUR_DEBUG;FOUR_ASSERTS_ENABLE"
            runtime "Debug"
            symbols "On"

        filter "configurations:Develpment"
            defines "FOUR_DEBUG;FOUR_ASSERTS_ENABLE"
            runtime "Release"
            optimize "On"

        filter "configurations:Release"
            defines "FOUR_RELEASE"
            runtime "Release"
            optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-Intermediate/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Four/vendor/spdlog/include",
        "Four/src",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Four"
    }

    filter "system:windows"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"
        systemversion "latest"

        defines
        {
            "FOUR_PLATFORM_WINDOWS",
            "USING_GLFW"
        }

        filter "configurations:Debug"
            defines "FOUR_DEBUG"
            runtime "Debug"
            symbols "on"

        filter "configurations:Develpment"
            defines "FOUR_DEVELOPMENT"
            runtime "Release"
            optimize "on"

        filter "configurations:Release"
            defines "FOUR_RELEASE"
            runtime "Release"
            optimize "on"

