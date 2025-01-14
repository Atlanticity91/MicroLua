project "Lua"
	kind "StaticLib"
	language "C"
	location "%{OutputDirs.Solution}"

	--- OUTPUT
	targetdir "%{OutputDirs.Bin}/%{cfg.buildcfg}/"
	debugdir "%{OutputDirs.Bin}/%{cfg.buildcfg}/"
	objdir "%{OutputDirs.BinInt}/%{prj.name}-%{cfg.buildcfg}"

	--- GLOBAL INCLUDES
	includedirs {
		"%{IncludeDirs.Lua}",
		"%{IncludeDirs.Lua}lua/"
	}

	externalincludedirs {
		"%{IncludeDirs.Lua}",
		"%{IncludeDirs.Lua}lua/"
	}

	--- GLOBAL SOURCE FILES
	files {
		"%{IncludeDirs.Lua}**.h",
		"%{IncludeDirs.Lua}**.c"
	}

	--- WINDOWS
	filter "system:windows"
		systemversion "latest"
		cdialect "C17"
		staticruntime "off"

		--- DEFINES
		defines { "WINDOWS" }

	--- LINUX
	filter "system:linux"
		systemversion "latest"

		--- DEFINES
		defines { "LINUX" }

	--- CONFIGURATION
	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"

		--- DEFINES
		defines "LUA_USE_APICHECK"

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
