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

#include "MicroLuaDebugTrace.h"

/**
 * @class MicroLuaDebugger
 * @brief Manage Lua debug capabilities and information for the MicroLua library.
 * 
 * @field m_hook Current Lua debug hook function.
 * @field m_flags Current Lua debug flags.
 * @field m_trace Current Lua trace instance.
 **/
class MicroLuaDebugger final { 

private:
	lua_Hook m_hook;
	uint32_t m_flags;
	MicroLuaDebugTrace m_trace;

public:
	/**
	 * @brief create and initialize Lua debugger instance.
	 **/
	MicroLuaDebugger( );

	/**
	 * @brief destroy and clean lua debugger instance.
	 **/
	~MicroLuaDebugger( ) = default;

	/**
	 * @brief set Lua debug hook function to specified hook.
	 * @param[in] hook The C hook function.
	 **/
	void Set( lua_Hook hook );

	/**
	 * @brief set Lua debug hook function to specified hook and is debug flags to 
	 *		  specified flags.
	 * @param[in] hook The C hook function.
	 * @param[in] flags The debug hook flags.
	 **/
	void Set( lua_Hook hook, const uint32_t flags );

	/**
	 * @brief reset the debug hook and flags to default values.
	 **/
	void Reset( );

	/**
	 * @brief add Lua debug flags to current flags. 
	 * @param[in] flags The Lua debug flags to add.
	 **/
	void Add( const uint32_t flags );

	/**
	 * @brief remove Lua debug flags from current flags.
	 * @param[in] flags The lua debug flags to remove.
	 **/
	void Remove( const uint32_t flags );

	/**
	 * @brief add a breakpoint to the Lua state.
	 * @param[in] breakpoint The new breakpoint to add.
	 **/
	void AddBreakpoint( const MicroLuaDebugBreakpoint& breakpoint );

	/**
	 * @brief add a breakpoint to the Lua state.
	 * @param[in] line The line number where the breakpoint is set within the Lua 
	 *			  script.
	 **/
	void AddBreakpoint( const uint32_t line );

	/**
	 * @brief add a breakpoint to the Lua state.
	 * @param[in] name The name of the Lua script where the breakpoint is located.
	 * @param[in] line The line number where the breakpoint is set within the Lua 
	 *			  script.
	 **/
	void AddBreakpoint( const std::string& name, const uint32_t line );

	void RemoveBreakpoint( const MicroLuaDebugBreakpoint& breakpoint );

	void RemoveBreakpoint( const uint32_t line );

	void RemoveBreakpoint( const std::string& name, const uint32_t line );

	void Enable( lua_State* lua_state );

	void Disable( lua_State* lua_state );

public:
	static bool GetHookIsBreakpoint(
		lua_Debug* lua_debug, 
		MicroLuaDebugTrace* trace 
	);

	static void SendHookMessage( 
		lua_Debug* lua_debug, 
		MicroLuaDebugTrace* trace 
	);

	static void ParseHookResponse( MicroLuaDebugTrace* trace );

private:
	static void DebugHook( lua_State* lua_state, lua_Debug* lua_debug );

public:
	lua_Hook GetHook( ) const;

	uint32_t GetFlags( ) const;

	const MicroLuaDebugTrace& GetTrace( ) const;

public:
	MicroLuaDebugger& operator=( const MicroLuaDebugger& other );

	MicroLuaDebugger& operator=( MicroLuaDebugger&& other ) noexcept;

};
