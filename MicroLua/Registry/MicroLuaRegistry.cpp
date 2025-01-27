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
MicroLuaRegistry::MicroLuaRegistry( )
    : m_thread_lock{ },
    m_libraries{ },
    m_globals{ }
{ }

bool MicroLuaRegistry::AddLibrary( const MicroLuaLibrary& library ) {
    auto thread_lock = std::unique_lock{ m_thread_lock };

    return m_libraries.Add( library );
}

bool MicroLuaRegistry::MergeLibrary( const MicroLuaLibrary& library ) {
    auto thread_lock = std::unique_lock{ m_thread_lock };

    return m_libraries.Merge( library );
}

bool MicroLuaRegistry::RemoveLibrary( const std::string& name ) {
    auto thread_lock = std::unique_lock{ m_thread_lock };

    return m_libraries.Remove( name );
}

void MicroLuaRegistry::EnableLibrary( const std::string& name ) {
    auto thread_lock = std::unique_lock{ m_thread_lock };

    m_libraries.Enable( name );
}

void MicroLuaRegistry::DisableLibrary( const std::string& name ) {
    auto thread_lock = std::unique_lock{ m_thread_lock };

    m_libraries.Disable( name );
}

bool MicroLuaRegistry::UnRegister( const std::string& name ) {
    auto thread_lock = std::unique_lock{ m_thread_lock };

    return m_globals.UnRegister( name );
}

bool MicroLuaRegistry::Load( const std::string& name, const std::string& path ) {
    auto thread_lock = std::unique_lock{ m_thread_lock };

    return false;
}

bool MicroLuaRegistry::UnLoad( const std::string& name ) {
    auto thread_lock = std::unique_lock{ m_thread_lock };

    return false;
}

void MicroLuaRegistry::AsignEnvironement( MicroLuaContext* lua_context ) {
    auto thread_lock = std::shared_lock{ m_thread_lock };

    if ( lua_context == nullptr || !lua_context->Create( ) )
        return;

    auto* lua_state = lua_context->GetState( );

    m_libraries.RegisterAll( lua_state );
    m_globals.AppendAll( lua_state );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaRegistry::GetExist( const std::string& name ) const {
    auto thread_lock = std::shared_lock{ m_thread_lock };

    return m_globals.GetExist( name );
}

MicroLuaValue MicroLuaRegistry::Get( const std::string& name ) const {
    auto thread_lock = std::shared_lock{ m_thread_lock };

    return std::move( m_globals.Get( name ) );
}

bool MicroLuaRegistry::GetHasLibrary( const std::string& name ) const {
    auto thread_lock = std::shared_lock{ m_thread_lock };

    return m_libraries.GetHasLibrary( name );
}

bool MicroLuaRegistry::GetIsLibraryEnabled( const std::string& name ) const {
    auto thread_lock = std::shared_lock{ m_thread_lock };

    return m_libraries.GetIsEnabled( name );
}

MicroLuaLibrary* MicroLuaRegistry::GetLibrary( const std::string& name ) {
    auto thread_lock = std::shared_lock{ m_thread_lock };

    return m_libraries.Get( name );
}
