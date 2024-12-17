# MicroLua
---
This repository contains the code for the Micro Lua Library, this project defined a minimal wrapper arround [lua](https://github.com/lua/lua) C API.

> [!CAUTION]
> Current repository documentation is not updated with actual code version.

# Cloning
> [!WARNING]
> This repository use submodules for Thirdparty. Make sure to setup submodules before any action. 

Using [git-cli](https://git-scm.com/) :

```
git clone --recursive https://github.com/Atlanticity91/MicroCore.git
```

Existing repositories can be updated manually :

```
git submodule init
git submodule update
```

# Build System
MicroCore as part of the Micro project use the [Premake5](https://github.com/premake/premake-core) build system. [Premake5](https://github.com/premake/premake-core) instance is present in this repository under Build/[Premake5](https://github.com/premake/premake-core).

Build files for [Premake5](https://github.com/premake/premake-core) are inside Build folder under :

| File 									  | Usage 								 								|
| --------------------------------------- | ------------------------------------------------------------------- |
| `Build/Build.lua` 					  | Define global solution build. 										|
| `Build/Build-Dependencies.lua` 		  | Define dependencies solution build. 								|
| `Build/Build-MicroLua.lua` 			  | Define MicroLua solution build.										|
| `Build/Test/Build-MicroTest.lua` 		  | Define test solution build.											|
| `Build/Thirdparty/Build-Lua.lua`  	  | Define [lua](https://github.com/lua/lua) thirdparty solution build. |

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
Documentation for the library can be found under [Documentation/index.html](https://atlanticity91.github.io/MicroLua/)
