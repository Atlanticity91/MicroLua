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

#include "MicroLuaMetatableStorage.h"

/**
 * MICRO_LUA_CLASS_GETAS_IMPL macro
 * @note : Wrapper for GetAs implementation of MicroLuaTable.
 **/
#define MICRO_LUA_CLASS_GETAS_IMPL\
	template<typename Type>\
	Type MicroLuaTable::GetAs( lua_State* lua_state, const std::string& name ) {\
		auto lua_value = Get( lua_state, name );\
		return lua_value.As<Type>( );\
	}

/**
 * MicroLuaValue struct
 * @note : Foward declaration of C++ Lua value wrapper.
 **/
class MicroLuaValue;

/**
 * MicroLuaTable final class
 * @note : Defined C++ representation of Lua table.
 **/
micro_class MicroLuaTable final {

	friend class MicroLuaValue;

private:
	std::string m_table;

public:
	/**
	 * Constructor
	 **/
	MicroLuaTable( );

	/**
	 * Constructor
	 * @param lua_state : Query Lua state.
	 * @param name : Query table name.
	 **/
	MicroLuaTable( lua_State* lua_state, const std::string& name );

	/**
	 * Move-Constructor
	 * @param other : Query class to move.
	 **/
	MicroLuaTable( MicroLuaTable&& other ) noexcept;

	/**
	 * Destructor
	 **/
	~MicroLuaTable( ) = default;

private:
	/**
	 * Constructor
	 * @param name : Query table name.
	 **/
	MicroLuaTable( micro_string name );

public:
	/**
	 * Set template function
	 * @note : Set table field value.
	 * @template Type : Query table field data type.
	 * @param lua_state : Query Lua state.
	 * @param name : Query field name.
	 * @param value : Query field value.
	 * @return : Return true when field 
	 **/
	template<typename Type>
	bool Set( lua_State* lua_state, const std::string& name, const Type value ) {
		auto lua_type = GetHas( lua_state, name );
		auto result   = ( micro::GetCompileLuaType<Type> == lua_type );

		if ( result ) {
			auto* lua_table = m_table.c_str( );
			auto* lua_name  = name.c_str( );

			lua_getglobal( lua_state, lua_table );

			micro::lua_push( lua_state, value );

			lua_setfield( lua_state, -2, lua_name );
		}

		return result;
	};

private:
	/**
	 * PopFront method
	 * @note : Pop field value to Lua top stack slot.
	 * @param lua_state : Query Lua state.
	 * @param name : Query field name.
	 **/
	void PopFront( lua_State* lua_state, const std::string& name );

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
	 * @note : Get field value from table.
	 * @param lua_state : Query Lua state.
	 * @param name : Query field name.
	 * @return : Return Lua value of the field.
	 **/
	MicroLuaValue Get( lua_State* lua_state, const std::string& name );

	/**
	 * GetFunction function
	 * @note : Get C function from the table. 
	 * @param lua_state : Query Lua state.
	 * @param name : Query function name.
	 * @return : Return C function pointer or NULL on failure.
	 **/
	lua_CFunction GetFunction( lua_State* lua_state, const std::string& name );

public:
	/**
	 * As template function
	 * @note : Convert Lua class to it's C++ counterpart.
	 * @template Type : Query C++ class type.
	 * @return : Return C++ counterpart of the Lua class, filled by Lua value.
	 */
	template<class Type>
		requires( !std::is_class<Type>::value )
	Type As( ) const {
		auto result = Type{ };

	#	ifdef MICRO_USE_CORE
		// TODO(Alves Quentin) : Class convertion code.
	#	endif

		return result;
	};

	/**
	 * GetAs template function
	 * @note : Get field casted as Type.
	 * @template : Type : Query field type.
	 * @param lua_state : Query Lua state.
	 * @param name : Query field name.
	 * @return : Return field value as Type.
	 **/
	template<typename Type>
	Type GetAs( lua_State* lua_state, const std::string& name );

public:
	/**
	 * Cast operator
	 * @note : Get is table is valid.
	 * @return : Return GetIsValid( ) call value.
	 **/
	operator bool ( ) const;

	/**
	 * Asign operator
	 * @note : Asign class based on another.
	 * @param other : Query other class.
	 * @return : Reference to current class.
	 **/
	MicroLuaTable& operator=( MicroLuaTable&& other );

};
