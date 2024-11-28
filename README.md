# MicroLua
---
This repository contains the code for the Micro Lua Library, this project defined a minimal wrapper arround [lua](https://github.com/lua/lua) C API.

> [!CAUTION]
> This repository use submodules for Thirdparty. Make sure to setup submodules before any action.
> `git submodule update --init --recursive`

# Build System
MicroLua as part of the Micro project use the [Premake5](https://github.com/premake/premake-core) build system. [Premake5](https://github.com/premake/premake-core) instance is present in this repository under Build/[Premake5](https://github.com/premake/premake-core).

Build files for [Premake5](https://github.com/premake/premake-core) are inside Build folder under :

| File  					     | Usage 								 					   |
| ------------------------------ | ----------------------------------------------------------- |
| `Build/Build.lua`  		 	 | Define global solution build. 		 					   |
| `Build/Build-Dependencies.lua` | Define global solutions dependencies. 		 			   |
| `Build/Build-MicroLua.lua`  	 | Define MicroLua solution build. 		 					   |
| `Test/Build-MicroTest.lua`	 | Define MicroTest solution build. 						   |
| `Thirdparty/Build-Lua.lua`	 | Define Lua solution build.								   |

## Windows
For Windows build you need at least visual studio 2022 community edition or visual studio C++.

To build the project files simply run Setup-Windows.bat

## Linux
> [!CAUTION]
> Linux isn't implemented yet.

To build the project files simply run Setup-Linux.sh

## Macos
> [!CAUTION]
> Macos isn't implemented yet.

To build the project files simply run Setup-Macos.sh

# Documentation
Documentation for the library can be found under [Documentation/index.html](./Documentation/index.html)

