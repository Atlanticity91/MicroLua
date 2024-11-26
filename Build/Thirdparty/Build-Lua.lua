project "Lua"
	kind "StaticLib"
	language "C"
	location "%{wks.location}/Solution/"

	files { 
		"%{IncludeDirs.lua}**.h",
		"%{IncludeDirs.lua}**.c"
	}

	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/"
	objdir "%{wks.location}/bin-int/%{prj.name}-%{cfg.buildcfg}"

	includedirs {
		"%{IncludeDirs.lua}",
		"%{IncludeDirs.lua}lua/"
	}

	--- CONFIGURATION
	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"

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

	--- WINDOWS
	filter "system:windows"
		systemversion "latest"
		defines "WINDOWS"
		cdialect "C17"
		staticruntime "off"

	--- LINUX
	filter "system:linux"
		systemversion "latest"
		defines { "LINUX" }
