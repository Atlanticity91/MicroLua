project "MicroTest"
	kind "SharedLib"
	language "C++"
	location "%{wks.location}/Solution/"

	targetdir "%{wks.location}/bin/%{cfg.buildcfg}/"
	objdir "%{wks.location}/bin-int/%{prj.name}-%{cfg.buildcfg}"

	includedirs "%{wks.location}/MicroLua/" 
	externalincludedirs "%{wks.location}/MicroLua/" 

	links "MicroLua"

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

		files {
			"%{IncludeDirs.test}/windows/**.h",
			"%{IncludeDirs.test}/windows/**.cpp"
		}

	--- LINUX
	filter "system:linux"
		systemversion "latest"
		defines { "LINUX" }

		files {
			"%{IncludeDirs.test}/linux/**.h",
			"%{IncludeDirs.test}/linux/**.cpp"
		}
