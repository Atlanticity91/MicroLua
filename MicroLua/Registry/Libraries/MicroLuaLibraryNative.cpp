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
MicroLuaLibraryNative::MicroLuaLibraryNative( )
	: MicroLuaLibraryNative{ { } }
{ }

MicroLuaLibraryNative::MicroLuaLibraryNative( const MicroLuaLibraryNative& other )
	: MicroLuaLibraryNative{ { } }
{
	m_functions = other.m_functions;
}

MicroLuaLibraryNative::MicroLuaLibraryNative( MicroLuaLibraryNative&& other ) noexcept
	: MicroLuaLibraryNative{ { } }
{ 
	m_functions = std::move( other.m_functions );
}

MicroLuaLibraryNative::MicroLuaLibraryNative( std::initializer_list<luaL_Reg> functions )
	: m_functions{ functions }
{ 
	m_functions.emplace( { NULL, NULL } );
}

void MicroLuaLibraryNative::Add( const luaL_Reg& function ) {
	if ( strlen( function.name ) == 0 || function.func == NULL )
		return;

	auto last = m_functions.end( ) - 1;

	m_functions.emplace( last, function );
}

void MicroLuaLibraryNative::Add( std::initializer_list<luaL_Reg> functions ) {
	for ( auto& function : functions )
		Add( function );
}

void MicroLuaLibraryNative::Add( micro_string name, lua_CFunction function ) {
	Add( luaL_Reg{ name, function } );
}

void MicroLuaLibraryNative::Extend( const MicroLuaLibraryNative& extension ) {
	if ( !extension.GetIsValid( ) )
		return;

	const auto& extension_list = extension.Get( );
	auto extension_first	   = extension_list.begin( );
	auto extension_last		   = extension_list.end( ) - 1;
	auto last				   = m_functions.end( ) - 1;

	m_functions.insert( last, extension_first, extension_last );
}

bool MicroLuaLibraryNative::Import( lua_State* lua_state ) {
	auto result = ( m_functions.size( ) > 0 );

	if ( result ) {
		const auto* functions = m_functions.data( );

		lua_newtable( lua_state );
		luaL_setfuncs( lua_state, functions, 0 );
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaLibraryNative::GetIsValid( ) const {
	return m_functions.size( ) > 1;
}

const std::vector<luaL_Reg>& MicroLuaLibraryNative::Get( ) const {
	return m_functions;
}
