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

#include <__micro_lua_pch.h>

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaClass::MicroLuaClass( )
	: m_table{ } 
{ }

MicroLuaClass::MicroLuaClass( lua_State* lua_state, const std::string& name )
	: MicroLuaClass{ }
{ 
	if ( lua_state == NULL )
		return;

	auto* lua_name = name.c_str( );

	lua_getglobal( lua_state, lua_name );

	if ( lua_istable( lua_state, MICRO_LUA_STACK_TOP ) )
		m_table = name;

	lua_pop( lua_state, 1 );
}

MicroLuaClass::MicroLuaClass( MicroLuaClass&& other )
	: m_table{ std::move( other ) }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaClass::MicroLuaClass( micro_string name )
	: m_table{ name }
{ }

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void MicroLuaClass::PopFront( lua_State* lua_state, const std::string& name ) {
	auto* lua_table = m_table.c_str( ); 
	auto* lua_name = name.c_str( );

	lua_getglobal( lua_state, lua_table );
	lua_pushstring( lua_state, lua_name );
	lua_gettable( lua_state, -2 );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaClass::GetIsValid( ) const { 
	return !m_table.empty( );
}

MicroLuaTypes MicroLuaClass::GetHas( lua_State* lua_state, const std::string& name ) {
	auto result = MicroLuaTypes::None;

	if ( lua_state != NULL && GetIsValid( ) ) {
		PopFront( lua_state, name );

		switch ( lua_type( lua_state, MICRO_LUA_STACK_TOP ) ) {
			case LUA_TBOOLEAN		: result = MicroLuaTypes::Boolean;  break;
			case LUA_TFUNCTION		: result = MicroLuaTypes::Function; break;
			case LUA_TUSERDATA		: result = MicroLuaTypes::Pointer;  break;
			case LUA_TLIGHTUSERDATA : result = MicroLuaTypes::Pointer;  break;
			case LUA_TSTRING		: result = MicroLuaTypes::String;   break;
			
			case LUA_TNUMBER : 
				if ( lua_isinteger( lua_state, MICRO_LUA_STACK_TOP ) )
					result = MicroLuaTypes::Integer;
				else
					result = MicroLuaTypes::Number;   
				
				break;

			default : break;
		}

		lua_pop( lua_state, 1 );
	}

	return result;
}

bool MicroLuaClass::GetHasField( lua_State* lua_state, const std::string& name ) {
	return GetHas( lua_state, name ) < MicroLuaTypes::Function;
}

bool MicroLuaClass::GetHasFunction( lua_State* lua_state, const std::string& name ) {
	return GetHas( lua_state, name ) == MicroLuaTypes::Function;
}

MicroLuaValue MicroLuaClass::Get( lua_State* lua_state, const std::string& name ) {
	if ( lua_state != NULL && GetIsValid( ) )
		PopFront( lua_state, name );

	return { lua_state };
}

lua_CFunction MicroLuaClass::GetFunction( lua_State* lua_state, const std::string& name ) {
	auto* lua_function = (lua_CFunction)NULL;

	if ( lua_state != NULL && GetIsValid( ) ) {
		PopFront( lua_state, name );

		if ( lua_iscfunction( lua_state, MICRO_LUA_STACK_TOP ) )
			lua_function = lua_tocfunction( lua_state, MICRO_LUA_STACK_TOP );

		lua_pop( lua_state, 1 );
	}

	return lua_function;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaClass::operator bool( ) const {
	return GetIsValid( );
}

MicroLuaClass& MicroLuaClass::operator=( MicroLuaClass&& other ) {
	m_table = std::move( other.m_table );

	return micro_self;
}
