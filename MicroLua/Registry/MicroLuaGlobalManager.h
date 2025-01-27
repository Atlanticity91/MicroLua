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

#include "Libraries/MicroLuaLibraryManager.h"

class MicroLuaGlobalManager final {

private:
    std::unordered_map<std::string, MicroLuaValue> m_globals;

public:
    MicroLuaGlobalManager( );

    ~MicroLuaGlobalManager( ) = default;

    bool UnRegister( const std::string& name );

    void Append( lua_State* lua_state, const std::string& name );

    void AppendAll( lua_State* lua_state );

private:
    void Append( 
        lua_State* lua_state, 
        const std::pair<std::string, MicroLuaValue>& pair 
    );

public:
    template<typename Type>
    bool Register( const std::string& name, const Type& value ) {
        auto lua_value = MicroLuaValue{ value };
        auto result    = GetExist( name );

        if ( !result ) {
            auto pair = std::make_pair( name, lua_value );

            m_globals.emplace( pair );

            result = true;
        }

        return result;
    };

public:
    bool GetExist( const std::string& name ) const;

    MicroLuaValue Get( const std::string& name ) const;

};
