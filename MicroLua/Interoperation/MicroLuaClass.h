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

#include "MicroLuaValue.h"

/**
 * MicroLuaClass final class
 * @note : Defined C++ representation of Lua table.
 **/
micro_class MicroLuaClass final {

private:
	micro_string m_name;

public:
	/**
	 * Constructor
	 **/
	MicroLuaClass( );

	/**
	 * Constructor
	 * @param lua_state : Query Lua state.
	 * @param name : Query table name.
	 **/
	MicroLuaClass( lua_State* lua_state, const std::string & name );

	/**
	 * Destructor
	 **/
	~MicroLuaClass( ) = default;

public:
	/**
	 * GetIsValid const function
	 * @note : Get is table is valid.
	 * @return : Return true when table is valid.
	 **/
	bool GetIsValid( ) const;

	/**
	 * GetHas function
	 * @note : Get type of an element of name name.
	 * @param lua_state : Query Lua state.
	 * @param name : Name of the element.
	 * @return : Return Lua type if table contain name.
	 **/
	MicroLuaTypes GetHas( lua_State* lua_state, const std::string& name );

	/**
	 * GetHasField function
	 * @note : Get if table has field with specific name.
	 * @param lua_state : Query Lua state.
	 * @param name : Query field name.
	 * @return : Return true when field is founded.
	 **/
	bool GetHasField( lua_State* lua_state, const std::string& name );

	/**
	 * GetHasFunction function
	 * @note : Get if table has function with specific name.
	 * @param lua_state : Query Lua state.
	 * @param name : Query function name.
	 * @return : Return true when function is founded.
	 **/
	bool GetHasFunction( lua_State* lua_state, const std::string& name );

	/**
	 * Get function
	 * @note :
	 * @param lua_state : Query Lua state.
	 * @param name : 
	 * @return :
	 **/
	MicroLuaValue Get( lua_State* lua_state, const std::string& name );

	/**
	 * GetFunction function
	 * @note :
	 * @param lua_state : Query Lua state.
	 * @param name :
	 * @return :
	 **/
	lua_CFunction GetFunction( lua_State* lua_state, const std::string& name );

public:
	/**
	 * As template function
	 * @note : 
	 * @template Type : Query C++ class type.
	 */
	template<class Type>
		requires( !std::is_class<Type>::value )
	Type As( ) const {
		auto result = Type{ };

	#	ifdef MICRO_USE_CORE
	#	endif

		return result;
	};

	/**
	 * 
	 * @note :
	 * @template Type :
	 * @param lua_state : Query Lua state.
	 * @param name :
	 * @return :
	 **/
	template<typename Type>
	Type GetAs( lua_State* lua_state, const std::string& name ) {
		auto result = Get( lua_state, name );

		return result.As<Type>( );
	};

public:
	/**
	 * Cast operator
	 * @note : Get is table is valid.
	 * @return : Return GetIsValid( ) call value.
	 **/
	operator bool ( ) const;

};
