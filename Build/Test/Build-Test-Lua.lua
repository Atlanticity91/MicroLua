project 'Test-Lua'
	kind 'SharedLib'
	language 'C++'
	location '%{OutputDirs.Solution}'

	--- OUTPUT
	targetdir '%{OutputDirs.Bin}%{cfg.buildcfg}/'
	debugdir '%{OutputDirs.Bin}%{cfg.buildcfg}/'
	objdir '%{OutputDirs.BinInt}%{prj.name}-%{cfg.buildcfg}'

	--- GLOBAL INCLUDES
	includedirs {
		'%{IncludeDirs.MicroLua}',
		'%{IncludeDirs.Lua}'
	}

	externalincludedirs {
		'%{IncludeDirs.MicroLua}',
		'%{IncludeDirs.Lua}'
	} 

	--- GLOBAL LINKS
	links 'MicroLua'

	--- WINDOWS
	filter 'system:windows'
		systemversion 'latest'
		cppdialect 'C++20'
		staticruntime 'off'
		
		--- DEFINES
		defines { 
			'WINDOWS',
			'_CRT_SECURE_NO_WARNINGS' 
		}

		--- SOURCE FILES
		files {
			'%{IncludeDirs.MicroLuaTest}windows/**.h',
			'%{IncludeDirs.MicroLuaTest}windows/**.cpp'
		}

	--- LINUX
	filter 'system:linux'
		systemversion 'latest'
		
		--- DEFINES
		defines { 'LINUX' }

		--- SOURCES FILES
		files {
			'%{IncludeDirs.MicroTest}linux/**.h',
			'%{IncludeDirs.MicroTest}linux/**.cpp'
		}
	
	--- CONFIGURATION
	filter 'configurations:Debug'
		defines { 'DEBUG' }
		runtime 'Debug'
		symbols 'On'

	filter 'configurations:Release'
		defines { 'RELEASE' }
		runtime 'Release'
		optimize 'On'
		symbols 'On'

	filter 'configurations:Dist'
		defines { 'DIST' }
		runtime 'Release'
		optimize 'On'
		symbols 'Off'
