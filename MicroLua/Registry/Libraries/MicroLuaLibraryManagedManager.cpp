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
MicroLuaLibraryManagedManager::MicroLuaLibraryManagedManager( ) 
	: m_libraries{ }
{ }

void MicroLuaLibraryManagedManager::Register( 
	const std::string& name, 
	const MicroLuaLibraryManaged& library 
) {
	auto pair = std::make_pair( name, library );

	m_libraries.emplace( pair );
}

void MicroLuaLibraryManagedManager::UnRegister( const std::string& name ) {
	m_libraries.erase( name );
}

void MicroLuaLibraryManagedManager::Import(
	lua_State* lua_state,
	const std::string& name
) {
	const auto* lua_name = name.c_str( );
	const auto iterator  = m_libraries.find( name );
	const auto length	 = iterator->second.GetLength( );
	const auto* data	 = micro_cast( iterator->second.GetData( ), const char* );

	luaL_loadbuffer( lua_state, data, length, lua_name );
}
