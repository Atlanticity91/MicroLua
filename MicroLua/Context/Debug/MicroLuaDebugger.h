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

class MicroLuaDebugger final { 

private:
	lua_Hook m_hook;
	uint32_t m_flags;
	MicroLuaDebugTrace m_trace;

public:
	MicroLuaDebugger( );

	~MicroLuaDebugger( ) = default;

	void Set( lua_Hook hook );

	void Set( lua_Hook hook, const uint32_t flags );

	void Add( const uint32_t flags );

	void Remove( const uint32_t flags );

	void AddBreakpoint( const MicroLuaDebugBreakpoint& breakpoint );

	void AddBreakpoint( const std::string& name, const uint32_t line );

	void RemoveBreakpoint( const MicroLuaDebugBreakpoint& breakpoint );

	void RemoveBreakpoint( const std::string& name, const uint32_t line );

	void Enable( lua_State* lua_state );

	void Disable( lua_State* lua_state );

public:
	static bool GetHookIsBreakpoint(
		lua_Debug* lua_debug, 
		MicroLuaDebugTrace* trace 
	);

	static void SendHookMessage( lua_Debug* lua_debug );

	static void ParseHookResponse( MicroLuaDebugTrace* trace );

private:
	static void DebugHook( lua_State* lua_state, lua_Debug* lua_debug );

public:
	lua_Hook GetHook( ) const;

	uint32_t GetFlags( ) const;

	MicroLuaDebugTrace& GetTrace( );

};
