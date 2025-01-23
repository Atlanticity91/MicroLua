/**
 *
 *  __  __ _             ___
 * |  \/  (_)__ _ _ ___ / __|___ _ _ ___
 * | |\/| | / _| '_/ _ \ (__/ _ \ '_/ -_)
 * |_|  |_|_\__|_| \___/\___\___/_| \___|
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

#ifdef MICRO_USE_CORE
#	include <MicroCore/MicroCore.h>
#else
#	include "MicroTraits.h"
#endif

extern "C" {
	#include <lua/lua.h>
	#include <lua/lualib.h>
	#include <lua/lauxlib.h>
};

#define MICRO_LUA_STACK_TOP ( -1 )

namespace micro { 

	/**
	 * lua_push template method
	 * @note : Wrapper for lua_push function.
	 * @template Type : Query push data type.
	 * @param lua_state : Query Lua state.
	 * @param data : Query data to push.
	 **/
	template<typename Type>
	void lua_push( lua_State* lua_state, const Type& data ) {
		micro_compile_if( std::is_integral<Type>::value )
			lua_pushinteger( lua_state, (lua_Integer)data );
		micro_compile_elif( std::is_floating_point<Type>::value )
			lua_pushnumber( lua_state, (lua_Number)data );
		micro_compile_elif( std::is_same<micro_string, Type>::value )
			lua_pushstring( lua_state, data );
		micro_compile_elif( std::is_same<lua_CFunction, Type>::value )
			lua_pushcfunction( lua_state, data );
		micro_compile_elif( std::is_pointer<Type>::value )
			lua_pushlightuserdata( lua_state, data );
		micro_compile_elif( std::is_reference<Type>::value )
			lua_pushlightuserdata( lua_state, micro_ptr_as( data, void* ) );
	};

};
