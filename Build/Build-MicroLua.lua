project "MicroLua"
	kind "StaticLib"
	language "C++"

	files {
		"../MicroLua/**.h",
		"../MicroLua/**.cpp" 
	}

	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/"
	objdir "%{wks.location}/bin-int/%{prj.name}-%{cfg.buildcfg}"

	includedirs {
		"%{wks.location}/MicroLua/",
		"%{IncludeDirs.lua}"
	}
	externalincludedirs { 
		"%{wks.location}/MicroLua/",
		"%{IncludeDirs.lua}"
	}

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
		
		defines { 
			"WINDOWS",
			"_CRT_SECURE_NO_WARNINGS" 
		}
		
		pchheader "__micro_lua_pch.h"
		pchsource "../MicroLua/__micro_lua_pch.cpp"

	--- LINUX
	filter "system:linux"
		systemversion "latest"
		defines { "LINUX" }
