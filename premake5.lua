workspace "Pholos"
	architecture "x64"
	startproject "Pholos"

	configurations	{ "Debug", "Release", "Testing" }

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

	filter "configurations:Release"
			defines "PH_RELEASE"
			optimize "On"

project "PholosTest"
	location "PholosTest"
	kind "ConsoleApp"
	language "C++"

    warnings "Extra"

	targetdir ("build/test/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/test/bin-int/" .. outputdir .. "/%{prj.name}")
	targetname "pholostest"

	files {
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
        "Pholos/src"
	}

    filter "system:windows"
            cppdialect "C++17"
            systemversion "latest"

	filter "configurations:Testing"
			defines "PH_TESTING"
			symbols "On"
