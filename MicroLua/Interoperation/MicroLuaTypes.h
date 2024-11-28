/**
 *
 *  __  __ _            _
 * |  \/  (_)__ _ _ ___| |  _  _ __ _
 * | |\/| | / _| '_/ _ \ |_| || / _` |
 * |_|  |_|_\__|_| \___/____\_,_\__,_|
 *
 * MIT License
 *
 * Copyright (c) 2024 Alves Quentin
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

#include "../Utils/MicroCore.h"

/**
 * MicroLuaTypes enum class
 * @note : Defined all Lua possible types.
 **/
micro_enum_class MicroLuaTypes : uint32_t {

	Boolean = 0,
	Integer,
	Number,
	String,
	Pointer,
	Function,
	None

};

namespace micro {

	#define MICRO_COMPILE_LUA_TYPE( TYPE, VALUE )\
		template<>\
		constexpr MicroLuaTypes GetCompileLuaType<TYPE> = MicroLuaTypes:: VALUE
		
	/**
	 * GetCompileLuaType template constexpr
	 * @note : Wrapper for compile time Lua type deduction.
	 * @template Type : Query type.
	 * @return : Return Lua type.
	 **/
	template<typename Type>
	constexpr MicroLuaTypes GetCompileLuaType =
		( std::is_pointer<Type>::value ) ? MicroLuaTypes::Pointer : MicroLuaTypes::None;

	MICRO_COMPILE_LUA_TYPE( lua_CFunction, Function );
	MICRO_COMPILE_LUA_TYPE( lua_Integer, Integer );
	MICRO_COMPILE_LUA_TYPE( lua_Number, Number );
	MICRO_COMPILE_LUA_TYPE( bool, Boolean );
	MICRO_COMPILE_LUA_TYPE( int8_t, Integer );
	MICRO_COMPILE_LUA_TYPE( int16_t, Integer );
	MICRO_COMPILE_LUA_TYPE( int32_t, Integer );
	MICRO_COMPILE_LUA_TYPE( float, Number ); 
	MICRO_COMPILE_LUA_TYPE( micro_string, String );
	MICRO_COMPILE_LUA_TYPE( std::string, String );

	/**
	 * GetLuaType template function
	 * @note : Get Lua type value for a Type.
	 * @template Type : Query type.
	 * @return : Return Lua type value.
	 **/
	template<typename Type>
	MicroLuaTypes GetLuaType( ) {
		return GetCompileLuaType<Type>;
	};

};
