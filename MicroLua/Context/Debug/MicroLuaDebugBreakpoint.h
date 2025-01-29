/**
 *
 *  __  __ _            _
 * |  \/  (_)__ _ _ ___| |  _  _ __ _
 * | |\/| | / _| '_/ _ \ |_| || / _` |
 * |_|  |_|_\__|_| \___/____\_,_\__,_|
 *
 * MIT License
 *
 * Copyright (c) 2024- Alves Quentin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **/

#pragma once

#include "MicroLuaDebugPipe.h"

/**
 * @struct MicroLuaDebugBreakpoint
 * @brief Encapsulate the data for breakpoint in Lua scripts.
 **/
struct MicroLuaDebugBreakpoint {

	std::string FileName;
	uint32_t FileLine;

	/**
	 * @brief Create and initialize an empty breakpoint.
	 **/
	MicroLuaDebugBreakpoint( );

	/**
	 * @brief Create and initialize a breakpoint for the default Lua stack.
	 * @param[in] line The line number where the breakpoint should be set in the 
	 *			  default Lua script.
	 **/
	MicroLuaDebugBreakpoint( const uint32_t line );

	/**
	 * @brief Creates and initializes a breakpoint with a specified script name 
	 *		  and line number.
	 * @param[in] name The name of the Lua script where the breakpoint is located.
	 * @param[in] line The line number where the breakpoint is set within the Lua 
	 *			  script.
	 **/
	MicroLuaDebugBreakpoint( const std::string& name, const uint32_t line );

	bool operator==( const MicroLuaDebugBreakpoint& other ) const;

};
