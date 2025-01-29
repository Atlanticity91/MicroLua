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
MicroLuaLibraryManaged::MicroLuaLibraryManaged( ) 
	: m_bytecodes{ }
{ }

MicroLuaLibraryManaged::MicroLuaLibraryManaged( const std::vector<uint8_t>& bytecodes )
	: m_bytecodes{ bytecodes }
{ }

MicroLuaLibraryManaged::MicroLuaLibraryManaged( std::vector<uint8_t>&& bytecodes ) noexcept
	: MicroLuaLibraryManaged{ }
{ 
	m_bytecodes = std::move( bytecodes );
}

MicroLuaLibraryManaged::MicroLuaLibraryManaged( const MicroLuaLibraryManaged& other )
	: MicroLuaLibraryManaged{ }
{ 
	m_bytecodes = other.m_bytecodes;
}

MicroLuaLibraryManaged::MicroLuaLibraryManaged( MicroLuaLibraryManaged&& other ) noexcept
	: MicroLuaLibraryManaged{ }
{ 
	m_bytecodes = std::move( other.m_bytecodes );
}

bool MicroLuaLibraryManaged::Compile( const std::string& source ) {
	const auto* lua_source = source.c_str( );
	const auto length	   = (uint32_t)source.size( );

	return Compile( lua_source, length );
}

bool MicroLuaLibraryManaged::Compile( const char* source, const uint32_t length ) {
	auto* lua_state = luaL_newstate( );
	auto result = false;
	
	if ( lua_state != NULL ) {
		if ( luaL_loadstring( lua_state, source ) == LUA_OK )
			result = ( lua_dump( lua_state, micro_ptr( MicroLuaPreprocessor::LuaWriter ), micro_ptr_as( m_bytecodes, void* ), 0 ) == LUA_OK );

		lua_close( lua_state );
	}

	return result;
}

bool MicroLuaLibraryManaged::Import( lua_State* lua_state ) {
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaLibraryManaged::GetIsValid( ) const {
	return m_bytecodes.size( ) > 0;
}

const uint8_t* MicroLuaLibraryManaged::GetData( ) const {
	return m_bytecodes.data( );
}

const uint32_t MicroLuaLibraryManaged::GetLength( ) const {
	return (uint32_t)m_bytecodes.size( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaLibraryManaged& MicroLuaLibraryManaged::operator=(
	std::vector<uint8_t>&& bytecodes
) noexcept {
	m_bytecodes = std::move( bytecodes );

	return micro_self;
}
