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
MicroLuaContext::MicroLuaContext( ) 
	: m_state{ NULL }
{ }

MicroLuaContext::MicroLuaContext( lua_State* lua_state )
{ 
	Terminate( );

	m_state = lua_state;
}

MicroLuaContext::MicroLuaContext( MicroLuaContext&& other )
	: m_state{ other.m_state } 
{
	other.m_state = NULL;
}

MicroLuaContext::~MicroLuaContext( ) {
	Terminate( );
}

bool MicroLuaContext::Create( ) {
	if ( GetIsValid( ) )
		Terminate( );

	m_state = luaL_newstate( );

	return GetIsValid( );
}

void MicroLuaContext::LoadDefaultLibraries( ) {
	if ( !GetIsValid( ) )
		return;

	luaL_openlibs( m_state );
}

void MicroLuaContext::LoadLibraries( std::initializer_list<lua_CFunction> libraries ) {
	if ( !GetIsValid( ) )
		return;

	for ( auto library : libraries )
		std::invoke( library, m_state );
}

bool MicroLuaContext::Inject( const std::string& source ) {
	auto result = false;

	if ( GetIsValid( ) && !source.empty( ) ) {
		auto* source_code = source.c_str( );

		result = ( luaL_dostring( m_state, source_code ) == LUA_OK );
	}

	return result;
}

bool MicroLuaContext::InjectFile( const std::string& path ) {
	auto result = false;

	if ( GetIsValid( ) && std::filesystem::exists( path ) ) {
		auto* source_path = path.c_str( );

		result = ( luaL_dofile( m_state, source_path ) == LUA_OK );
	}

	return result;
}

void MicroLuaContext::Terminate( ) {
	if ( GetIsValid( ) )
		lua_close( m_state );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaContext::GetIsValid( ) const {
	return ( m_state != NULL );
}

lua_State* MicroLuaContext::Get( ) const {
	return m_state;
}

MicroLuaValue MicroLuaContext::Pop( ) const {
	return { m_state };
}

MicroLuaValue MicroLuaContext::Get( const std::string& name ) const {
	auto* lua_name = name.c_str( );
	auto lua_type = LUA_TNIL;

	if ( GetIsValid( ) )
		lua_type = lua_getglobal( m_state, lua_name );

	return ( lua_type != LUA_TTABLE ) ? MicroLuaValue{ m_state } : MicroLuaValue{ lua_name };
}

MicroLuaClass MicroLuaContext::GetClass( const std::string& name ) const {
	return { m_state, name };
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaContext::operator bool ( ) const {
	return GetIsValid( );
}

MicroLuaContext::operator lua_State* ( ) const {
	return Get( );
}
