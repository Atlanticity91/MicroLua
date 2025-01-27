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

#pragma once 

#include "MicroLuaLibrary.h"

class MicroLuaLibraryManager final {

private:
	std::unordered_map<std::string, MicroLuaLibrary> m_libraries;

public:
	MicroLuaLibraryManager( );

	~MicroLuaLibraryManager( ) = default;

	bool Add( const MicroLuaLibrary& library );

	bool Merge( const MicroLuaLibrary& library );

	bool Remove( const std::string& name );

	void RegisterAll( lua_State* lua_state );

	void Register( lua_State* lua_state, const std::string& name );

	void Enable( const std::string& name );

	void Disable( const std::string& name );

public:
	bool GetHasLibrary( const std::string& name ) const;

	bool GetIsEnabled( const std::string& name ) const;

	MicroLuaLibrary* Get( const std::string& name );

};
