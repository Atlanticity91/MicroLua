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

#include "MicroLuaGlobalManager.h"

class MicroLuaRegistry final {

private:
    mutable std::shared_mutex m_thread_lock;
    MicroLuaLibraryManager m_libraries;
    MicroLuaGlobalManager m_globals;

public:
    MicroLuaRegistry( );

    ~MicroLuaRegistry( ) = default;

    bool AddLibrary( const MicroLuaLibrary& library );

    bool MergeLibrary( const MicroLuaLibrary& library );

    bool RemoveLibrary( const std::string& name );

    void EnableLibrary( const std::string& name );

    void DisableLibrary( const std::string& name );

    bool UnRegister( const std::string& name );

    bool Load( const std::string& name, const std::string& path );
    
    bool UnLoad( const std::string& name );

    void AsignEnvironement( MicroLuaContext* lua_context );

public:
    template<typename Type>
    bool Register( const std::string& name, const Type& value ) {
        auto thread_lock = std::unique_lock{ m_thread_lock };

        return m_globals.Register( name, value );
    };

public:
    bool GetExist( const std::string& name ) const;

    MicroLuaValue Get( const std::string& name ) const;

    bool GetHasLibrary( const std::string& name ) const;

    bool GetIsLibraryEnabled( const std::string& name ) const;

    MicroLuaLibrary* GetLibrary( const std::string& name );

};
