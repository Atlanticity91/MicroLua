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
	: m_libraries{ },
	m_native_manager{ },
	m_managed_manager{ }
{ }

bool MicroLuaLibraryManager::Register(
	const std::string& name, 
	const MicroLuaLibraryNative& library
) {
	auto iterator = m_libraries.find( name );
	auto result	  = false;

	if ( iterator == m_libraries.end( ) && library.GetIsValid( ) ) {
		auto pair = std::make_pair( name, MicroLuaLibraryState{ true, false } );

		m_native_manager.Register( name, library );
		m_libraries.emplace( pair );

		result = true;
	}

	return result;
}

bool MicroLuaLibraryManager::Register( 
	const std::string& name, 
	const MicroLuaLibraryManaged& library 
) {
	auto iterator = m_libraries.find( name );
	auto result = false;

	if ( iterator == m_libraries.end( ) && library.GetIsValid( ) ) {
		auto pair = std::make_pair( name, MicroLuaLibraryState{ true, true } );

		m_managed_manager.Register( name, library );
		m_libraries.emplace( pair );

		result = true;
	}

	return result;
}

bool MicroLuaLibraryManager::Extend(
	const std::string& name,
	const MicroLuaLibraryNative& extension
) {
	auto iterator = m_libraries.find( name );
	auto result	  = false;

	if ( iterator != m_libraries.end( ) ) {
		m_native_manager.Extend( name, extension );

		result = true;
	} else
		result = Register( name, extension );

	return result;
}

bool MicroLuaLibraryManager::UnRegister( const std::string& name ) {
	auto iterator = m_libraries.find( name );
	auto result	  = false;

	if ( iterator != m_libraries.end( ) ) {
		if ( iterator->second.IsManaged )
			m_managed_manager.UnRegister( name );
		else
			m_native_manager.UnRegister( name );

		result = ( m_libraries.erase( name ) == 1 );
	}

	return result;
}

bool MicroLuaLibraryManager::Enable( const std::string& name ) {
	auto iterator = m_libraries.find( name );
	auto result   = ( iterator != m_libraries.end( ) );

	if ( result )
		iterator->second.IsEnabled = true;

	return result;
}

bool MicroLuaLibraryManager::Disable( const std::string& name ) {
	auto iterator = m_libraries.find( name );
	auto result   = ( iterator != m_libraries.end( ) );

	if ( result )
		iterator->second.IsEnabled = false;

	return result;
}

void MicroLuaLibraryManager::ImportAll( lua_State* lua_state ) {
	if ( lua_state == NULL )
		return;

	for ( auto& iterator : m_libraries ) {
		if ( !iterator.second.IsEnabled )
			continue;

		ImportInternal( lua_state, iterator );
	}
}

void MicroLuaLibraryManager::Import( lua_State* lua_state, const std::string& name ) {
	if ( lua_state == NULL )
		return;

	auto iterator = m_libraries.find( name );

	if ( iterator != m_libraries.end( ) && iterator->second.IsEnabled )
		ImportInternal( lua_state, micro_ref( iterator ) );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void MicroLuaLibraryManager::ImportInternal( 
	lua_State* lua_state,
	const std::pair<std::string, MicroLuaLibraryState>& iterator
) {
	if ( iterator.second.IsManaged )
		m_managed_manager.Import( lua_state, iterator.first );
	else
		m_native_manager.Import( lua_state, iterator.first );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaLibraryManager::GetHasLibrary( const std::string& name ) const {
	return m_libraries.find( name ) != m_libraries.end( );
}

bool MicroLuaLibraryManager::GetIsEnabled( const std::string& name ) const {
	auto iterator = m_libraries.find( name );
	auto result   = false;

	if ( iterator != m_libraries.end( ) )
		result = iterator->second.IsEnabled;
	
	return result;
}

bool MicroLuaLibraryManager::GetIsManaged( const std::string& name ) const {
	auto iterator = m_libraries.find( name );
	auto result   = false;

	if ( iterator != m_libraries.end( ) )
		result = iterator->second.IsManaged;

	return result;
}
