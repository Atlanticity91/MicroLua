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

#include "MicroLuaClass.h"

/**
 * MicroLuaValue class final
 * @note : Defined wrapper for Lua stack element.
 **/
micro_class MicroLuaValue final {

	friend class MicroLuaContext;

	MicroLuaTypes m_type;
	MicroLuaData m_data;

public:
	/**
	 * Constructor
	 **/
	MicroLuaValue( );

	/**
	 * Constructor
	 * @param lua_state : Query Lua state.
	 **/
	MicroLuaValue( lua_State* lua_state );

	/**
	 * Destructor
	 **/
	~MicroLuaValue( ) = default;

private:
	/**
	 * Constructor
	 * @param table : Query table name.
	 **/
	MicroLuaValue( micro_string table );

public:
	/**
	 * Constructor
	 * @template : Query data type.
	 * @param data : Query data.
	 **/
	template<typename Type>
	MicroLuaValue( const Type& data )
		: m_data{ }
	{
		constexpr auto lua_type = micro::GetCompileLuaType<Type>;
		
		m_type = lua_type;

		micro_compile_if( lua_type == MicroLuaTypes::Boolean )
			m_data.Integer = ( data == true ) ? 1 : 0;
		micro_compile_elif( lua_type == MicroLuaTypes::Integer )
			m_data.Integer = lua_Integer{ data };
		micro_compile_elif( lua_type == MicroLuaTypes::Number )
			m_data.Number = lua_Number{ data };
		micro_compile_elif( 
			lua_type == MicroLuaTypes::String  ||
			lua_type == MicroLuaTypes::Pointer
		)
			m_data.Pointer = micro_cast( data, void* );
		micro_compile_elif( lua_type == MicroLuaTypes::Function )
			m_data.Function = data;
	};

public:
	/**
	 * GetType const function
	 * @note : Get Lua type.
	 **/
	MicroLuaTypes GetType( ) const;

	/**
	 * GetHasValue const function
	 * @note : Get if value is valid.
	 * @return : Return if value is valid.
	 **/
	bool GetHasValue( ) const;

	/**
	 * Is const function
	 * @note : Get if data type is a specific type.
	 * @param lua_type : Query lua type.
	 * @return : Return true when data type match lua_type.
	 **/
	bool Is( const MicroLuaTypes lua_type ) const;

public:
	/**
	 * As template function
	 * @note : Get data casted as Type when type match Lua type.
	 * @template Type : Query data type.
	 * @return : Return data casted as Type.
	 **/
	template<typename Type>
	Type As( ) {
		constexpr auto lua_type = micro::GetCompileLuaType<Type>;
		auto result				= Type{ };

		if ( lua_type == m_type ) {
			micro_compile_if( std::is_same<MicroLuaClass, Type>::value )
				result = MicroLuaClass{ micro_cast( m_data.Pointer, micro_string ) };
			micro_compile_elif( lua_type == MicroLuaTypes::Boolean )
				result = ( m_data.Integer == 0 );
			micro_compile_elif( lua_type == MicroLuaTypes::Integer )
				result = (Type)( m_data.Integer );
			micro_compile_elif( lua_type == MicroLuaTypes::Number )
				result = (Type)( m_data.Number );
			micro_compile_elif( lua_type == MicroLuaTypes::String ) {
				micro_compile_if( std::is_same<std::string, Type>::value )
					result = std::move( std::string{ micro_cast( m_data.Pointer, micro_string ) } );
				micro_compile_else
					result = micro_cast( m_data.Pointer, micro_string );
			} micro_compile_elif( lua_type == MicroLuaTypes::Pointer )
				result = micro_cast( m_data.Pointer, Type* );
			micro_compile_elif( lua_type == MicroLuaTypes::Function )
				result = m_data.Function;
		}

		return std::move( result );
	};

	/**
	 * Is template const function
	 * @note : Get data casted as Type when type match Lua type.
	 * @template : Query type.
	 * @return : Return Is( ) call value. 
	 **/
	template<typename Type>
	micro_inline bool Is( ) const {
		const auto lua_type = micro::GetLuaType<Type>( );

		return Is( lua_type );
	};

};

MICRO_LUA_CLASS_GETAS_IMPL;
