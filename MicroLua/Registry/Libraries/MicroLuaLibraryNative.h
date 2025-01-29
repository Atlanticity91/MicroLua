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

micro_class MicroLuaLibraryNative final : public MicroLuaLibrary {

private:
    std::vector<luaL_Reg> m_functions;

public:
    MicroLuaLibraryNative( );

    MicroLuaLibraryNative( const MicroLuaLibraryNative& other );

    MicroLuaLibraryNative( MicroLuaLibraryNative&& other ) noexcept;

    MicroLuaLibraryNative( std::initializer_list<luaL_Reg> functions );

    void Add( const luaL_Reg& function );

    void Add( std::initializer_list<luaL_Reg> functions );

    void Add( micro_string name, lua_CFunction function );

    void Extend( const MicroLuaLibraryNative& extension );

    micro_implement( bool Import( lua_State* lua_state ) );

public:
    micro_implement( bool GetIsValid( ) const );

    const std::vector<luaL_Reg>& Get( ) const;

};
