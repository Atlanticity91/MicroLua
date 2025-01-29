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
MicroLuaGlobalManager::MicroLuaGlobalManager( )
	: m_globals{ }
{ }

bool MicroLuaGlobalManager::UnRegister( const std::string& name ) {
	return m_globals.erase( name ) == 1;
}

void MicroLuaGlobalManager::Import( lua_State* lua_state, const std::string& name ) {
	if ( lua_state == NULL || name.empty( ) )
		return;

	auto iterator = m_globals.find( name );

	if ( iterator != m_globals.end( ) )
		Import( lua_state, micro_ref( iterator ) );
}

void MicroLuaGlobalManager::ImportAll( lua_State* lua_state ) {
	if ( lua_state == NULL )
		return;

	for ( const auto& iterator : m_globals )
		Import( lua_state, iterator );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void MicroLuaGlobalManager::Import(
	lua_State* lua_state,
	const std::pair<std::string, MicroLuaValue>& iterator
) {
	const auto* lua_name = iterator.first.c_str( );

	iterator.second.Push( lua_state );

	lua_setglobal( lua_state, lua_name );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaGlobalManager::GetExist( const std::string& name ) const {
	return m_globals.find( name ) != m_globals.end( );
}

MicroLuaValue MicroLuaGlobalManager::Get( const std::string& name ) const {
	auto iterator = m_globals.find( name );
	auto result   = MicroLuaValue{ };

	if ( iterator != m_globals.end( ) )
		result = iterator->second;

	return result;
}
