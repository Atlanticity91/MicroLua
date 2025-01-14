--- TOOL INCLUDES
include "Premake/CSExtensions.lua"
include "Premake/VSExtensions.lua"
include "Build-Dependencies.lua"

--- PROJECT CONFIGURATION
workspace "Micro Solution"
	architecture "x64"
	startproject "MicroCore"
	location "../"
	configurations { 
		"Debug", 
		"Release", 
		"Dist" 
	}

    --- WINDOWS
    filter "system:windows"
        --- GLOBAL FLAGS
        flags "MultiProcessorCompile"
        
        --- WORKSPACE-WIDE BUILD OPTIONS FOR MSVC
        buildoptions { 
            "/EHsc",
            "/Zc:preprocessor", 
            "/Zc:__cplusplus" 
        }

	--- THIRDPARTY PROJECTS
	group "Thirdparty"
		include "Thirdparty/Build-Lua.lua"
	--- TEST PROJECTS
	group "Test"
		include "Test/Build-MicroTest.lua"
	group ""

	--- MAIN PROJECT
	include "Build-MicroLua.lua"
