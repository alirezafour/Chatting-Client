-- premake 5
workspace "Four"
    architecture "x64"

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

include "Four/vendor/GLFW" -- Adding glfw premake
include "Four/vendor/Glad" -- Adding glad premake

project "Four"
    location "Four"
    kind "SharedLib"
    language "C++"

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
        "%{IncludeDir.Glad}"
    }

	links -- link static libs
	{ 
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FOUR_PLATFORM_WINDOWS",
            "FOUR_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

        filter "configurations:Debug"
            defines "FOUR_DEBUG;FOUR_ASSERTS_ENABLE"
            buildoptions "/MDd"
            symbols "On"

        filter "configurations:Develpment"
            defines "FOUR_DEBUG;FOUR_ASSERTS_ENABLE"
            buildoptions "/MD"
            symbols "On"
            optimize "On"

        filter "configurations:Release"
            defines "FOUR_RELEASE"
            buildoptions "/MD"
            optimize "On"

        --filters { "system:windows", "configurations:Develpment"}
        --    buildoptions "/MT" -- multi thread runtime lib

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
        "Four/src"
    }

    links
    {
        "Four"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FOUR_PLATFORM_WINDOWS",
        }

        filter "configurations:Debug"
            defines "FOUR_DEBUG"
            buildoptions "/MDd"
            symbols "On"

        filter "configurations:Develpment"
            defines "FOUR_DEVELOPMENT"
            buildoptions "/MD"
            symbols "On"
            optimize "On"

        filter "configurations:Release"
            defines "FOUR_RELEASE"
            buildoptions "/MD"
            optimize "On"

        --filters { "system:windows", "configurations:Develpment"}
        --    buildoptions "/MT" -- multi thread runtime lib


