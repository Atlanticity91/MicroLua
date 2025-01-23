project 'MicroLuaDebugger'
	kind 'SharedLib'
	language 'C#'
	csversion '10.0'
	dotnetframework '4.8'
	location "%{OutputDirs.Solution}"

	--- OUTPUT
	targetdir '%{OutputDirs.Bin}/%{cfg.buildcfg}/'
	debugdir '%{OutputDirs.Bin}/%{cfg.buildcfg}/'
	objdir '%{OutputDirs.BinInt}/%{prj.name}-%{cfg.buildcfg}'

	--- GLOBAL SOURCE FILES
	files { 
		'%{ExtensionDirs.MicroLuaDebugger}**.cs',
		'%{ExtensionDirs.MicroLuaDebugger}**.resx',
		'%{ExtensionDirs.MicroLuaDebugger}**.vsixmanifest',
		'%{ExtensionDirs.MicroLuaDebugger}**.vsct',
		'%{ExtensionDirs.MicroLuaDebugger}**.xaml'
	}

	--- GLOBAL LINKS
	nuget {
		'Microsoft.VisualStudio.Sdk:17.0.31903.148',
		'Community.VisualStudio.Toolkit.17:17.0.507',
		'Community.VisualStudio.VSCT:16.0.29.6',
		'Microsoft.VSSDK.BuildTools:17.9.3168'
	}

	--- LINKS
	links {
		'System',
		'System.Design',
		'System.Xaml',
		'PresentationCore',
		'PresentationFramework',
		'WindowsBase',
		'System.ComponentModel.Composition'
	}

	--- DEBUG COMMAND
	debugcommand '%{ExtensionDirs.Devenv}'

	--- DEBUG ARGUMENTS 
	debugargs { '/rootsuffix Exp' }

	--- POST BUILD COMMANDS
	postbuildcommands {
		'msbuild "%{wks.location}/Solution/MicroLuaDebugger.csproj" /p:Configuration=Debug'
	}

	-- Add custom properties required for a VSIX project
    --filter {}
    buildoptions {
    	'<PropertyGroup>',
    	'  <GeneratePackageOnBuild>true</GeneratePackageOnBuild>',
    	'  <IncludeBuildOutput>false</IncludeBuildOutput>',
    	'  <OutputType>Library</OutputType>',
    	'</PropertyGroup>'
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
