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

#include "MicroLuaContext.h"

class MicroLuaContextManager final { 

private:
    std::mutex m_mutex;
    std::vector<MicroLuaContext> m_context;

public:
    MicroLuaContextManager( );

    ~MicroLuaContextManager( );

    bool Create( const uint32_t thread_count );

    bool LoadDefaultLibraries( );
    bool LoadLibrary( lua_CFunction lua_library );
    bool LoadLibraries( std::initializer_list<lua_CFunction> libraries );

    bool Inject( const std::string lua_source );
    bool InjectFile( const std::string& file_path );

    uint32_t Acquire( );

    void Release( const uint32_t context_handle );

    void Terminate( );

public:
    bool GetExist( const uint32_t context_handle ) const;

    MicroLuaContext* GetContext( const uint32_t context_handle );

};
