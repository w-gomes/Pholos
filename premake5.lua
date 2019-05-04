workspace "Pholos"
	configurations	{ "Debug", "Release" }
	architecture "x64"
	startproject "Pholos"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Pholos"
	location "Pholos"
	kind "ConsoleApp"
	language "C++"

    warnings "Extra"

	targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/bin-int/" .. outputdir .. "/%{prj.name}")
	targetname "pholos"

	files {
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/lib/fmt/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	filter "configurations:Debug"
		defines "PH_DEBUG"
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "PH_RELEASE"
		optimize "On"
		runtime "Release"