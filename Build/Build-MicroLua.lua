project "MicroLua"
	kind "StaticLib"
	language "C++"
	location "%{OutputDirs.Solution}"

	--- OUTPUT
	targetdir "%{OutputDirs.Bin}/%{cfg.buildcfg}/"
	debugdir "%{OutputDirs.Bin}/%{cfg.buildcfg}/"
	objdir "%{OutputDirs.BinInt}/%{prj.name}-%{cfg.buildcfg}"

	--- GLOBAL INCLUDES
	includedirs {
		"%{IncludeDirs.MicroLua}",
		"%{IncludeDirs.Lua}"
	}

	externalincludedirs { 
		"%{IncludeDirs.MicroLua}",
		"%{IncludeDirs.Lua}"
	}

	--- PRECOMPILED HEADERS
	pchheader "__micro_lua_pch.h"

	--- GLOBAL SOURCE FILES
	files {
		"%{IncludeDirs.MicroLua}/**.h",
		"%{IncludeDirs.MicroLua}/**.cpp" 
	}

	--- GLOBAL LINKS
	links "Lua"

	--- CONFIGURATION
	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		defines { "DIST" }
		runtime "Release"
		optimize "On"
		symbols "Off"

	--- WINDOWS
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++20"
		staticruntime "off"
		
		--- DEFINES
		defines { 
			"WINDOWS",
			"_CRT_SECURE_NO_WARNINGS" 
		}

		--- PRECOMPILED HEADERS
		pchsource "../MicroLua/__micro_lua_pch.cpp"

	--- LINUX
	filter "system:linux"
		systemversion "latest"
		defines { "LINUX" }
