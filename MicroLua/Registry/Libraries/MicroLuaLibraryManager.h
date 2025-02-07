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

#include "MicroLuaLibraryManagedManager.h"

micro_struct MicroLuaLibraryState {

	bool IsEnabled;
	bool IsManaged;

	MicroLuaLibraryState( ) 
		: MicroLuaLibraryState{ true, false }
	{ };

	MicroLuaLibraryState( const bool is_enabled, const bool is_managed )
		: IsEnabled{ is_enabled },
		IsManaged{ is_managed }
	{ };

};

micro_class MicroLuaLibraryManager final {

private:
	std::unordered_map<std::string, MicroLuaLibraryState> m_libraries;
	MicroLuaLibraryNativeManager m_native_manager;
	MicroLuaLibraryManagedManager m_managed_manager;

public:
	MicroLuaLibraryManager( );

	~MicroLuaLibraryManager( ) = default;

	bool Register( const std::string& name, const MicroLuaLibraryNative& library );

	bool Register( const std::string& name, const MicroLuaLibraryManaged& library );

	bool Extend( const std::string& name, const MicroLuaLibraryNative& extension );

	bool UnRegister( const std::string& name );

	bool Enable( const std::string& name );

	bool Disable( const std::string& name );

	void ImportAll( lua_State* lua_state );

	void Import( lua_State* lua_state, const std::string& name );

private:
	void ImportInternal( 
		lua_State* lua_state,
		const std::pair<std::string, MicroLuaLibraryState>& pair
	);

public:
	bool GetHasLibrary( const std::string& name ) const;

	bool GetIsEnabled( const std::string& name ) const;

	bool GetIsManaged( const std::string& name ) const;

};
