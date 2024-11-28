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
	 * Inject function
	 * @note : Inject Lua program to Lua stack.
	 * @param source : Lua source code to load.
	 * @return : Return true when Lua loading succeeded.
	 **/
	bool Inject( const std::string& source );

	/**
	 * InjectFile function
	 * @note : Inject Lua file to Lua stack.
	 * @param path : Query Lua source file.
	 * @return : Return true when Lua loading succeded.
	 **/
	bool InjectFile( const std::string& path );

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
	 * @note : Push string to Lua stack.
	 * @param name : Query string name on Lua stack.
	 * @param function : Query string.
	 **/
	template<>
	void Push<micro_string>(
		const std::string& name,
		const micro_string& string
	) {
		auto* lua_name = name.c_str( );

		lua_pushstring( m_state, ( string != NULL ) ? string : "" );
		lua_setglobal( m_state, lua_name );
	};
	
	/**
	 * Push method
	 * @note : Push string to Lua stack.
	 * @param name : Query string name on Lua stack.
	 * @param function : Query string.
	 **/
	template<>
	void Push<std::string>(
		const std::string& name,
		const std::string& string
	) {
		auto* lua_string = string.c_str( );
		auto* lua_name   = name.c_str( );
		
		lua_pushstring( m_state, lua_string );
		lua_setglobal( m_state, lua_name );
	};

	/**
	 * Call template function
	 * @note : Call method from Lua stack.
	 * @template Args : Query arguments types.
	 * @param method : Query method name.
	 * @param args : Query argument list.
	 * @return : Return true when method calling succeeded.
	 **/
	template<typename... Args>
	bool Call( const std::string& method, Args&&... args ) {
		auto result = false;

		if ( GetIsValid( ) && !method.empty( ) )
			result = CallInternal( method, 0, std::forward<Args>( args )... );

		return result;
	};

	/**
	 * Call template function
	 * @note : Load and call method from Lua stack.
	 * @template Args : Query arguments types.
	 * @param path : Query source code path.
	 * @param method : Query method name.
	 * @param args : Query argument list.
	 * @return : Return true when method calling succeeded.
	 **/
	template<typename... Args>
	bool CallFile( 
		const std::string& path,
		const std::string& method, 
		Args&&... args 
	) {
		InjectFile( path );

		return Call<Args...>( method, std::forward<Args>( args )... );
	};

	/**
	 * CallFunction template function
	 * @note : Call function from Lua stack.
	 * @template ReturnType : Query function call returned element type.
	 * @template Args : Query arguments types.
	 * @param function : Query function name.
	 * @param args : Query argument list.
	 * @return : Return Lua function result casted as ReturnType.
	 **/
	template<typename ReturnType, typename... Args >
	ReturnType CallFunction( const std::string& function, Args&&... args ) {
		if ( GetIsValid( ) && !function.empty( ) )
			CallInternal( function, 1, std::forward<Args>( args )... );

		return PopAs<ReturnType>( );
	};

	/**
	 * CallFileFunction template function
	 * @note : Load and call function from Lua stack.
	 * @template ReturnType : Query function call returned element type.
	 * @template Args : Query arguments types.
	 * @param function : Query function name.
	 * @param args : Query argument list.
	 * @return : Return Lua function result casted as ReturnType.
	 **/
	template<typename ReturnType, typename... Args >
	ReturnType CallFileFunction(
		const std::string& path,
		const std::string& function,
		Args&&... args
	) {
		InjectFile( path );

		return CallFunction<Args...>( function, std::forward<Args>( args )... );
	};

private:
	/**
	 * CallInternal template function
	 * @note : Internal wrapper for Lua function call.
	 * @template Args : Query arguments types.
	 * @param name : Query function name.
	 * @param return_count : Query function return count.
	 * @param args : Query argument list.
	 * @return : Return true when Lua call succeeded.
	 **/
	template<typename... Args>
	bool CallInternal( 
		const std::string& name, 
		const uint32_t return_count,
		Args&&... args 
	) {
		auto* lua_name = name.c_str( );
		auto result    = false;

		lua_getglobal( m_state, lua_name );

		if ( lua_isfunction( m_state, MICRO_LUA_STACK_TOP ) ) {
			micro_variadic_expand(
				constexpr auto lua_type = micro::GetCompileLuaType<Args>;

				micro_compile_if( lua_type == MicroLuaTypes::Boolean )
					lua_pushboolean( m_state, args );
				micro_compile_elif( lua_type == MicroLuaTypes::Integer )
					lua_pushinteger( m_state, (lua_Integer)args );
				micro_compile_elif( lua_type == MicroLuaTypes::Number )
					lua_pushnumber( m_state, (lua_Number)args );
				micro_compile_elif( lua_type == MicroLuaTypes::String )
					lua_pushstring( m_state, args );
				micro_compile_elif( lua_type == MicroLuaTypes::Pointer )
					lua_pushlightuserdata( m_state, micro_cast( args, void* ) );
			);

			result = lua_pcall( m_state, (uint32_t)( sizeof...( Args ) ), return_count, 0 ) == LUA_OK;
		}

		return result;
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

	/**
	 * GetClass const function
	 * @note : Get class instance from Lua stack.
	 * @param name : Query class instance name.
	 * @return : Return C++ Lua class wrapper. 
	 **/
	MicroLuaClass GetClass( const std::string& name ) const;

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

	/**
	 * GetClassAs template class
	 * @note : Get class from Lua stack.
	 * @template Type : Query class type.
	 * @param name : Query element name.
	 * @return : Return class instance.
	 **/
	template<class Type>
	Type GetClassAs( const std::string& name ) const { 
		auto lua_class = GetClass( name );

		return lua_class.As<Type>( );
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
