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

#include "MicroLuaMetatableStorage.h"

/**
 * MicroLuaContext class final
 * @note : Wrapper for basic Lua C API interaction.
 **/
micro_class MicroLuaContext final {

private:
	lua_State* m_state;

public:
	/**
	 * Constructor
	 **/
	MicroLuaContext( );

	/**
	 * Move-Constructor
	 * @param other : Query context to move.
	 **/
	MicroLuaContext( MicroLuaContext&& other );

	/**
	 * Destructor
	 **/
	~MicroLuaContext( );

	/**
	 * Create function
	 * @note : Create Lua state.
	 * @return : Return true when Lua state creation succeeded.
	 **/
	bool Create( );

	/**
	 * LoadDefaultLibraries method
	 * @note : Load default libraries to Lua.
	 **/
	void LoadDefaultLibraries( );

	/**
	 * LoadLibraries method
	 * @note : Load libraries to Lua.
	 * @param libraries : Query libraries to open.
	 **/
	void LoadLibraries( std::initializer_list<lua_CFunction> libraries );

	/**
	 * Load function
	 * @note : Load Lua program to Lua state.
	 * @param source : Lua source code to load.
	 * @return : Return true when Lua loading succeeded.
	 **/
	bool Load( const std::string& source );

	/**
	 * LoadFile function
	 * @note : Load Lua file to Lua state.
	 * @param path : Query Lua source file.
	 * @return : Return true when Lua loading succeded.
	 **/
	bool LoadFile( const std::string& path );

	/**
	 * Execute function
	 * @note : Run Lua program from source.
	 * @param source : Lua source code to execute.
	 * @return : Return true when Lua execution succeeded.
	 **/
	bool Execute( const std::string& source );

	/**
	 * ExecuteFile function
	 * @note : Run Lua program from a file.
	 * @param path : Query Lua source code file path.
	 * @return : Return true when Lua execution succeeded.
	 **/
	bool ExecuteFile( const std::string& path );

	/**
	 * Terminate method
	 * @note : Terminate the Lua state.
	 **/
	void Terminate( );

public:
	/**
	 * Regiser template method
	 * @note : Register class to Lua metatables.
	 * @template Type : Query class Type.
	 **/
	template<class Type>
	void Regiser( ) {
		const auto* lua_type = micro::GetLuaMetatable<Type>( );
	
		// TODO(Alves Quentin) : Metatable implementation.
	};

	/**
	 * Regiser template method
	 * @note : Register class to Lua metatables.
	 * @template Type : Query class Type list.
	 **/
	template<class... Type>
	void Register( ) {
		micro_variadic_expand( Regiser<Type>( ); );
	};

	/**
	 * Push template method
	 * @note : Push element on top of Lua stack.
	 * @template Type : Query element type.
	 * @param name : Query element name on Lua stack.
	 * @param element : Query element to push on Lua stack.
	 **/
	template<typename Type>
	void Push( const std::string& name, const Type& element ) { };

	/**
	 * Push method
	 * @note : Push boolean to Lua stack.
	 * @param name : Query boolean name on Lua stack.
	 * @param element : Query boolean value.
	 **/
	template<>
	void Push<bool>( const std::string& name, const bool& element ) {
		auto* lua_name = name.c_str( );

		lua_pushboolean( m_state, element );
		lua_setglobal( m_state, lua_name );
	};

	/**
	 * Push method
	 * @note : Push integer to Lua stack.
	 * @param name : Query integer name on Lua stack.
	 * @param element : Query integer value.
	 **/
	template<>
	void Push<lua_Integer>( 
		const std::string& name, 
		const lua_Integer& element
	) { 
		auto* lua_name = name.c_str( );

		lua_pushinteger( m_state, element );
		lua_setglobal( m_state, lua_name );
	};

	/**
	 * Push method
	 * @note : Push number to Lua stack.
	 * @param name : Query number name on Lua stack.
	 * @param element : Query number value.
	 **/
	template<>
	void Push<lua_Number>(
		const std::string& name,
		const lua_Number& element
	) { 
		auto* lua_name = name.c_str( );

		lua_pushnumber( m_state, element );
		lua_setglobal( m_state, lua_name );
	};

	/**
	 * Push method
	 * @note : Push integer to Lua stack.
	 * @param name : Query integer name on Lua stack.
	 * @param element : Query integer value.
	 **/
	template<>
	micro_inline void Push<int8_t>( 
		const std::string& name, 
		const int8_t& element
	) {
		Push( name, lua_Integer{ element } );
	};

	/**
	 * Push method
	 * @note : Push integer to Lua stack.
	 * @param name : Query integer name on Lua stack.
	 * @param element : Query integer value.
	 **/
	template<>
	micro_inline void Push<int16_t>(
		const std::string& name,
		const int16_t& element
	) {
		Push( name, lua_Integer{ element } );
	};

	/**
	 * Push method
	 * @note : Push integer to Lua stack.
	 * @param name : Query integer name on Lua stack.
	 * @param element : Query integer value.
	 **/
	template<>
	micro_inline void Push<int32_t>( 
		const std::string& name,
		const int32_t& element 
	) {
		Push( name, lua_Integer{ element } );
	};
	
	/**
	 * Push method
	 * @note : Push number to Lua stack.
	 * @param name : Query number name on Lua stack.
	 * @param element : Query number value.
	 **/
	template<>
	micro_inline void Push<float>(
		const std::string& name,
		const float& element
	) {
		Push( name, lua_Number{ element } );
	};

	/**
	 * Push method
	 * @note : Push C function to Lua stack.
	 * @param name : Query function name on Lua stack.
	 * @param function : Query function wrapped inside a lua_CFunction.
	 **/
	template<>
	void Push<lua_CFunction>(
		const std::string& name,
		const lua_CFunction& function
	) {
		if ( function == NULL )
			return;

		auto* lua_name = name.c_str( );

		lua_pushcclosure( m_state, function, 0 );
		lua_setglobal( m_state, lua_name );
	};

public:
	/**
	 * GetIsValid const function
	 * @note : Get if Lua state is valid.
	 * @return : Return true when Lua state is valid.
	 **/
	bool GetIsValid( ) const;

	/**
	 * Get const function
	 * @note : Get Lua state.
	 * @return : Return Lua state value.
	 **/
	lua_State* Get( ) const;

	/**
	 * Pop const function
	 * @note : Get last element from Lua stack.
	 * @return : Return Lua last element stack wrapped inside MicroLuaValue.
	 **/
	MicroLuaValue Pop( ) const;

	/**
	 * Get const function
	 * @note : Get element from Lua stack.
	 * @param name : Query element name.
	 * @return : Return Lua last element stack wrapped inside MicroLuaValue.
	 **/
	MicroLuaValue Get( const std::string& name ) const;

public:
	/**
	 * PopAs template const function
	 * @note : Pop last element from Lua stack.
	 * @template Type : Query element type.
	 * @return : Return Pop( ) value casted as Type.
	 **/
	template<typename Type>
	Type PopAs( ) const { 
		auto result = Pop( );

		return result.As<Type>( );
	};

	/**
	 * GetAs template const function
	 * @note : Get element from Lua stack.
	 * @template Type : Query element type.
	 * @param name : Query name.
	 * @return : Return Get( ) call casted as Type.
	 **/
	template<typename Type>
	Type GetAs( const std::string& name ) const {
		auto result = Get( name );

		return result.As<Type>( );
	};

public:
	/**
	 * Cast operator
	 * @note : Get if Lua state is valid.
	 * @return : Return GetIsValid( ) call value.
	 **/
	operator bool ( ) const;

	/**
	 * Cast operator
	 * @note : Get Lua state.
	 * @return : Return Get( ) call value.
	 **/
	operator lua_State* ( ) const;

};
