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

#include "__micro_lua_pch.h"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaValue::MicroLuaValue( )
	: m_type{ MicroLuaTypes::None },
	m_data{ }
{ }

MicroLuaValue::MicroLuaValue( lua_State* lua_state )
	: MicroLuaValue{ } 
{
	if ( lua_state == NULL )
		return;

	if ( lua_isboolean( lua_state, MICRO_LUA_STACK_TOP ) ) {
		m_type = MicroLuaTypes::Boolean;
		m_data.Integer = lua_toboolean( lua_state, MICRO_LUA_STACK_TOP );
	} else if ( lua_isinteger( lua_state, MICRO_LUA_STACK_TOP ) ) {
		m_type = MicroLuaTypes::Integer;
		m_data.Integer = lua_tointeger( lua_state, MICRO_LUA_STACK_TOP );
	} else if ( lua_isnumber( lua_state, MICRO_LUA_STACK_TOP ) ) {
		m_type = MicroLuaTypes::Number;
		m_data.Number = lua_tonumber( lua_state, MICRO_LUA_STACK_TOP );
	} else if ( lua_isstring( lua_state, MICRO_LUA_STACK_TOP ) ) {
		m_type = MicroLuaTypes::String;
		m_data.Pointer = micro_cast( lua_tostring( lua_state, MICRO_LUA_STACK_TOP ), void* );
	} else if ( lua_iscfunction( lua_state, MICRO_LUA_STACK_TOP ) ) {
		m_type = MicroLuaTypes::Function;
		m_data.Function = lua_tocfunction( lua_state, MICRO_LUA_STACK_TOP );
	} else if (
		lua_isuserdata( lua_state, MICRO_LUA_STACK_TOP ) ||
		lua_islightuserdata( lua_state, MICRO_LUA_STACK_TOP )
	) {
		m_type = MicroLuaTypes::Pointer;
		m_data.Pointer = lua_touserdata( lua_state, MICRO_LUA_STACK_TOP );
	} else if ( lua_istable( lua_state, MICRO_LUA_STACK_TOP ) ) {
		m_type = MicroLuaTypes::Class;
		// TODO( ALVES Quentin ) : MANAGE TABLE
	}

	lua_pop( lua_state, 1 );
}

MicroLuaValue::MicroLuaValue( const MicroLuaValue& other )
	: MicroLuaValue{ }
{
	m_type = other.m_type;
	m_data = other.m_data;
}

MicroLuaValue::MicroLuaValue( MicroLuaValue&& other ) noexcept
	: MicroLuaValue{ }
{
	m_type = other.m_type;
	m_data = other.m_data;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaValue::GetHasValue( ) const {
	return m_type != MicroLuaTypes::None;
}

MicroLuaTypes MicroLuaValue::GetType( ) const {
	return m_type;
}

const MicroLuaData& MicroLuaValue::GetData( ) const {
	return m_data;
}

bool MicroLuaValue::Is( const MicroLuaTypes lua_type ) const {
	return m_type == lua_type;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaValue::operator bool ( ) const {
	return GetHasValue( );
}

MicroLuaValue& MicroLuaValue::operator=( const MicroLuaValue& other ) {
	m_type = other.m_type;
	m_data = other.m_data;

	return micro_self;
}
