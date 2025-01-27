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
MicroLuaContextManager::MicroLuaContextManager( )
    : m_mutex{ },
    m_context{ }
{ }

MicroLuaContextManager::~MicroLuaContextManager( ) 
{
    Terminate( );
}

bool MicroLuaContextManager::Create( const uint32_t thread_count ) {
    auto result = false;

    m_context.resize( (size_t)thread_count );

    for ( auto& context : m_context ) {
        result = context.Create( );

        if ( !result )
            break;
    }

    return result;
}

bool MicroLuaContextManager::LoadDefaultLibraries( ) {
    return false;
}

bool MicroLuaContextManager::LoadLibrary( lua_CFunction lua_library ) {
    return false;
}

bool MicroLuaContextManager::LoadLibraries( 
    std::initializer_list<lua_CFunction> libraries 
) {
    return false;
}

bool MicroLuaContextManager::Inject( const std::string lua_source ) {
    return false;
}

bool MicroLuaContextManager::InjectFile( const std::string& file_path ) {
    return false;
}

uint32_t MicroLuaContextManager::Acquire( ) {
    auto context_handle = (uint32_t)0;

    for ( auto& context : m_context ) {
        auto lock = std::lock_guard( m_mutex );

        if ( !context.GetIsInUse( ) ) {
            context.Acquire( );

            break;
        }

        context_handle += 1;
    }

    return context_handle;
}

void MicroLuaContextManager::Release( const uint32_t context_handle ) {
    if ( GetExist( context_handle ) )
        m_context[ context_handle ].Release( );
}

void MicroLuaContextManager::Terminate( ) {
    for ( auto& context : m_context )
        context.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaContextManager::GetExist( const uint32_t context_handle ) const {
    return context_handle < (uint32_t)m_context.size( );
}

MicroLuaContext* MicroLuaContextManager::Get( const uint32_t context_handle ) {
    auto* result = micro_cast( nullptr, MicroLuaContext* );

    if ( GetExist( context_handle ) )
        result = micro_ptr( m_context[ context_handle] );

    return result;
}
