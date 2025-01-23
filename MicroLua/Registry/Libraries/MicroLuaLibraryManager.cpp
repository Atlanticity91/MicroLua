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
MicroLuaLibraryManager::MicroLuaLibraryManager( ) 
	: m_libraries{ }
{ }

bool MicroLuaLibraryManager::Add( const MicroLuaLibrary& library ) {
	auto result = false;

	if ( m_libraries.find( library.Name ) == m_libraries.end( ) ) {
		auto pair = std::make_pair( library.Name, library );

		m_libraries.emplace( pair );

		result = true;
	}

	return result;
}

void MicroLuaLibraryManager::Merge( const MicroLuaLibrary& library ) {
	auto pair = m_libraries.find( library.Name );

	if ( pair != m_libraries.end( ) )
		pair->second.Merge( library );
	else
		Add( library );
}

void MicroLuaLibraryManager::Enable( const std::string& name ) {
	auto pair = m_libraries.find( name );

	if ( pair != m_libraries.end( ) )
		pair->second.Enable( );
}

void MicroLuaLibraryManager::Disable( const std::string& name ) {
	auto pair = m_libraries.find( name );

	if ( pair != m_libraries.end( ) ) 
		pair->second.Disable( );
}

void MicroLuaLibraryManager::RegisterAll( lua_State* lua_state ) {
	for ( auto& pair : m_libraries )
		pair.second.Register( lua_state );
}

void MicroLuaLibraryManager::Register( lua_State* lua_state, const std::string& name ) {
	auto pair = m_libraries.find( name );

	if ( pair != m_libraries.end( ) )
		pair->second.Register( lua_state );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaLibraryManager::GetIsEnabled( const std::string& name ) const {
	auto result = false;
	auto pair   = m_libraries.find( name );

	if ( pair != m_libraries.end( ) )
		result = pair->second.GetIsEnabled( );
	
	return result;
}

MicroLuaLibrary* MicroLuaLibraryManager::GetLibrary( const std::string& name ) {
	auto* result = (MicroLuaLibrary*)nullptr;
	auto pair = m_libraries.find( name );

	if ( pair != m_libraries.end( ) )
		result = micro_ptr( pair->second );

	return result;
}
