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
	: m_name{ NULL }
{ }

MicroLuaClass::MicroLuaClass( lua_State* lua_state, const std::string& name )
	: MicroLuaClass{ }
{ 
	if ( lua_state == NULL )
		return;

	auto* lua_name = name.c_str( );

	lua_getglobal( lua_state, lua_name );

	if ( lua_istable( lua_state, MICRO_LUA_STACK_TOP ) == 1 )
		m_name = lua_name;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaClass::GetIsValid( ) const { 
	return ( m_name != NULL ) && strlen( m_name ) > 0;
}

MicroLuaTypes MicroLuaClass::GetHas( lua_State* lua_state, const std::string& name ) {
	return MicroLuaTypes::None;
}

bool MicroLuaClass::GetHasField( lua_State* lua_state, const std::string& name ) {
	return false;
}

bool MicroLuaClass::GetHasFunction( lua_State* lua_state, const std::string& name ) {
	return false;
}

MicroLuaValue MicroLuaClass::Get( lua_State* lua_state, const std::string& name ) {
	return { };
}

lua_CFunction MicroLuaClass::GetFunction( lua_State* lua_state, const std::string& name ) {
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaClass::operator bool( ) const {
	return GetIsValid( );
}
