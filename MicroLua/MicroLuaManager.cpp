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
MicroLuaManager::MicroLuaManager( )
    : m_thread_locker{ },
    m_preprocessor{ },
    m_registry{ },
    m_context{ }
{ }

MicroLuaManager::~MicroLuaManager( ) {
    Terminate( );
}

bool MicroLuaManager::Create( const uint32_t context_count ) {
    Terminate( );

    auto thread_lock = std::unique_lock{ m_thread_locker };

    return  m_preprocessor.Create( ) && 
            m_context.Create( context_count );
}

bool MicroLuaManager::Add( const std::string& name, const MicroLuaLibraryNative& library ) {
    return m_registry.Add( name, library );
}

bool MicroLuaManager::Add( const std::string& name, const MicroLuaLibraryManaged& library ) {
    return m_registry.Add( name, library );
}

bool MicroLuaManager::Extend( 
    const std::string& name, 
    const MicroLuaLibraryNative& extension 
) {
    return m_registry.Extend( name, extension );
}

bool MicroLuaManager::Remove( const std::string& name ) {
    return m_registry.Remove( name );
}

bool MicroLuaManager::Enable( const std::string& name ) {
    return m_registry.Enable( name );
}

bool MicroLuaManager::Disable( const std::string& name ) {
    return m_registry.Disable( name );
}

bool MicroLuaManager::UnRegister( const std::string& name ) {
    return m_registry.UnRegister( name );
}

uint32_t MicroLuaManager::Acquire( ) {
    auto thread_lock    = std::unique_lock{ m_thread_locker };
    auto context_handle = m_context.Acquire( );

    if ( m_context.GetExist( context_handle ) ) {
        auto* lua_context = m_context.Get( context_handle );

        m_registry.AsignEnvironement( lua_context );
    }

    return context_handle;
}

void MicroLuaManager::Release( uint32_t& context_handle ) {
    auto thread_lock = std::unique_lock{ m_thread_locker };

    m_context.Release( context_handle );
}

void MicroLuaManager::Terminate( ) {
    auto thread_lock = std::unique_lock{ m_thread_locker };

    m_preprocessor.Terminate( );
    m_context.Terminate( );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaManager::GetGlobalExist( const std::string& name ) const {
    return m_registry.GetGlobalExist( name );
}

MicroLuaValue MicroLuaManager::GetGlobal( const std::string& name ) const {
    return m_registry.GetGlobal( name );
}

bool MicroLuaManager::GetLibraryExist( const std::string& name ) const {
    return m_registry.GetLibraryExist( name );
}

bool MicroLuaManager::GetIsLibraryEnabled( const std::string& name ) const {
    return m_registry.GetIsLibraryEnabled( name );
}

bool MicroLuaManager::GetIsLibraryManaged( const std::string& name ) const {
    return m_registry.GetIsLibraryManaged( name );
}

bool MicroLuaManager::GetContextExist( const uint32_t context_handle ) const {
    return m_context.GetExist( context_handle );
}

MicroLuaContext* MicroLuaManager::GetContext( const uint32_t context_handle ) {
    return m_context.Get( context_handle );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaContext* MicroLuaManager::operator[]( const uint32_t context_handle ) {
    return GetContext( context_handle );
}
