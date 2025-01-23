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
MicroLuaLibrary::MicroLuaLibrary( )
	: MicroLuaLibrary{ false, "", { } }
{ }

MicroLuaLibrary::MicroLuaLibrary( const MicroLuaLibrary& other )
	: MicroLuaLibrary{ other.IsEnabled, other.Name, { } }
{
	Functions = std::move( other.Functions );
}

MicroLuaLibrary::MicroLuaLibrary( MicroLuaLibrary&& other ) noexcept
	: MicroLuaLibrary{ }
{
	IsEnabled = other.IsEnabled;
	Name	  = std::move( other.Name );
	Functions = std::move( other.Functions );
}

MicroLuaLibrary::MicroLuaLibrary( const std::string& name )
	: MicroLuaLibrary{ false, name, { } }
{ }

MicroLuaLibrary::MicroLuaLibrary(
	const std::string& name,
	std::initializer_list<luaL_Reg> functions
)
	: MicroLuaLibrary{ true, name, functions }
{ }

MicroLuaLibrary::MicroLuaLibrary(
	const bool is_enabled,
	const std::string& name, 
	std::initializer_list<luaL_Reg> functions 
)
	: IsEnabled{ is_enabled },
	Name{ name },
	Functions{ functions }
{ 
	Functions.push_back( { NULL, NULL } );
}

void MicroLuaLibrary::Add( const luaL_Reg& function ) {
	if ( function.name == NULL || strlen( function.name ) == 0 || function.func == NULL )
		return;

	auto iterator_last = Functions.end( );

	Functions.insert( iterator_last - 1, function );
}

void MicroLuaLibrary::Add( micro_string name, lua_CFunction function ) {
	Add( { name, function } );
}

void MicroLuaLibrary::Merge( std::initializer_list<luaL_Reg> functions ) {
	auto count = functions.size( ) + functions.size( );

	Functions.resize( count );

	for ( const auto& function : functions ) {
		auto last = Functions.end( );

		Functions.insert( last - 1, function );
	}
}

void MicroLuaLibrary::Merge( const std::vector<luaL_Reg>& functions ) {
	auto merge_first = functions.begin( );
	auto merge_last  = functions.end( );
	auto last		 = Functions.end( );

	Functions.insert( last - 1, merge_first, merge_last );
}

void MicroLuaLibrary::Merge( const MicroLuaLibrary& other ) {
	Merge( other.Functions );
}

void MicroLuaLibrary::Register( lua_State* lua_state ) {
	if ( lua_state == NULL || !GetIsEnabled( ) )
		return;

	const auto* functions = Functions.data( );
	const auto* name = Name.c_str( );

	if ( Functions.size( ) > 0 ) {
		lua_newtable( lua_state );
		luaL_setfuncs( lua_state, functions, 0 );
	} else
		lua_pushnil( lua_state );

	lua_setglobal( lua_state, name );
}

void MicroLuaLibrary::Enable( ) {
	IsEnabled = true;
}

void MicroLuaLibrary::Disable( ) {
	IsEnabled = false;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaLibrary::GetIsEnabled( ) const {
	return IsEnabled;
}
