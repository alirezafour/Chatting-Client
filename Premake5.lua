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

project "Four"
    location "Four"
    kind "SharedLib"
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
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FOUR_PLATFORM_WINDOWS",
            "FOUR_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

        filter "configurations:Debug"
            defines "FOUR_DEBUG"
            symbols "On"

        filter "configurations:Develpment"
            defines "FOUR_DEVELOPMENT"
            symbols "On"
            optimize "On"

        filter "configurations:Shipping"
            defines "FOUR_SHIPPING"
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
            symbols "On"

        filter "configurations:Develpment"
            defines "FOUR_DEVELOPMENT"
            symbols "On"
            optimize "On"

        filter "configurations:Shipping"
            defines "FOUR_SHIPPING"
            optimize "On"

        --filters { "system:windows", "configurations:Develpment"}
        --    buildoptions "/MT" -- multi thread runtime lib


