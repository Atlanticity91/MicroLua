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
MicroLuaContext::MicroLuaContext( ) 
    : m_in_use{ false },
    m_state{ NULL },
    m_returns{ }
#   ifdef DEBUG
    , m_debugger{ }
#   endif
{ }

MicroLuaContext::MicroLuaContext( lua_State* lua_state )
    : MicroLuaContext{ }
{
    Terminate( );

    m_in_use = true;
    m_state  = lua_state;
}

MicroLuaContext::MicroLuaContext( const MicroLuaContext& other )
    : MicroLuaContext{ }
{
    Terminate( );

    m_in_use   = true;
    m_state    = other.m_state;
    m_returns  = other.m_returns;

#   ifdef DEBUG
    m_debugger = other.m_debugger;
#   endif
}

MicroLuaContext::MicroLuaContext( MicroLuaContext&& other ) noexcept
    : MicroLuaContext{ }
{
    Terminate( );

    m_state    = other.m_state;
    m_returns  = std::move( other.m_returns );
    
#   ifdef DEBUG
    m_debugger = std::move( other.m_debugger );
#   endif

    Acquire( );

    other.m_state = NULL;
}

MicroLuaContext::~MicroLuaContext( ) { 
    Terminate( );
}

bool MicroLuaContext::Create( ) {
    Terminate( );

    if ( m_state = luaL_newstate( ) )
        Acquire( );

    return GetIsValid( );
}

#ifdef DEBUG
    void MicroLuaContext::SetDebugHook( lua_Hook lua_hook ) {
        if ( lua_hook == NULL )
            return;

        m_debugger.Set( lua_hook );
    }

    void MicroLuaContext::SetDebugHook( lua_Hook hook, const uint32_t flags ) {
        if ( hook == NULL )
            return;

        m_debugger.Set( hook, flags );
    }

    void MicroLuaContext::ResetDebugHook( ) {
        m_debugger.Reset( );
    }

    void MicroLuaContext::AddDebugFlag( const uint32_t flags ) {
        m_debugger.Add( flags );
    }

    void MicroLuaContext::RemoveDebugFlag( const uint32_t flags ) {
        m_debugger.Remove( flags );
    }

    void MicroLuaContext::AddBreakpoint( const MicroLuaDebugBreakpoint& breakpoint ) {
        m_debugger.AddBreakpoint( breakpoint );
    }

    void MicroLuaContext::AddBreakpoint( const std::string& name, const uint32_t line ) {
        m_debugger.AddBreakpoint( { name, line } );
    }

    void MicroLuaContext::RemoveBreakpoint( const MicroLuaDebugBreakpoint& breakpoint ) {
        m_debugger.RemoveBreakpoint( breakpoint );
    }

    void MicroLuaContext::RemoveBreakpoint( const std::string& name, const uint32_t line ) {
        m_debugger.RemoveBreakpoint( { name, line } );
    }
#endif

bool MicroLuaContext::LoadDefaultLibraries( ) {
    auto result = false;

    if ( GetIsInUse( ) ) {
        luaL_openlibs( m_state );

        result = true;
    }

    return result;
}

bool MicroLuaContext::LoadLibrary( lua_CFunction lua_library ) {
    auto result = false;

    if ( GetIsInUse( ) && lua_library != NULL )
        result = ( std::invoke( lua_library, m_state ) == 1 );

    return result;
}

bool MicroLuaContext::LoadLibraries( std::initializer_list<lua_CFunction> libraries ) {
    auto result = false;

    if ( GetIsInUse( ) ) {
        for ( auto* library : libraries ) {
            if ( library == NULL )
                continue;
            
            if ( !( result = ( std::invoke( library, m_state ) == 1 ) ) )
                 break;
        }
    }

    return result;
}

bool MicroLuaContext::Inject( const std::string lua_source ) {
    auto result = false;

    if ( GetIsInUse( ) && !lua_source.empty( ) ) {
        auto* source = lua_source.c_str( );

        result = ( luaL_dostring( m_state, source ) == LUA_OK );
    }

    return result;
}

bool MicroLuaContext::InjectFile( const std::string& file_path ) {
    auto result = false;

    if ( GetIsInUse( ) && std::filesystem::exists( file_path ) ) {
        auto* source = file_path.c_str( );

        result = ( luaL_dofile( m_state, source ) == LUA_OK );
    }

    return result;
}

bool MicroLuaContext::Execute( const std::string& lua_source ) {
    auto result = false;

    if ( GetIsInUse( ) && !lua_source.empty( ) ) {
        auto* source = lua_source.c_str( );
        auto guard   = MicroLuaStackGuard{ m_state };

        result = ( luaL_dostring( m_state, source ) == LUA_OK );
    }

    return result;
}

void MicroLuaContext::Terminate( ) {
    if ( GetIsValid( ) ) {
#       ifdef DEBUG
        m_debugger.Disable( m_state );
#       endif

        lua_close( m_state );

        m_in_use = false;
        m_state  = NULL;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE ===
////////////////////////////////////////////////////////////////////////////////////////////
void MicroLuaContext::Acquire( ) {
    m_in_use = true;

    // TODO( ALVES Quentin ) : Copy stack globals
    
#   ifdef DEBUG
    m_debugger.Enable( m_state );
#   endif
}

void MicroLuaContext::Release( ) {
    m_in_use = false;
}

void MicroLuaContext::AcquireReturn( uint32_t return_count ) {
    m_returns.resize( (size_t)return_count );

    while ( return_count-- > 0 )
        m_returns[ return_count ] = MicroLuaValue{ m_state };
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaContext::GetIsValid( ) const {
    return ( m_state != NULL );
}

bool MicroLuaContext::GetIsInUse( ) const {
    return GetIsValid( ) && m_in_use;
}

lua_State* MicroLuaContext::GetState( ) const {
    return m_state;
}

MicroLuaValue MicroLuaContext::Pop( const std::string& name ) {
    auto* lua_name = name.c_str( );
    auto value     = MicroLuaValue{ };

    if ( GetIsInUse( ) ) {
        lua_getglobal( m_state, lua_name );

        value = MicroLuaValue{ m_state };
    }

    return value;
}

const std::vector<MicroLuaValue>& MicroLuaContext::PopReturns( ) const {
    return m_returns;
}

#ifdef DEBUG
    MicroLuaDebugger& MicroLuaContext::GetDebugger( ) {
        return m_debugger;
    }

    lua_Hook MicroLuaContext::GetDebugHook( ) const {
        return m_debugger.GetHook( );
    }

    uint32_t MicroLuaContext::GetDebugFlags( ) const {
        return m_debugger.GetFlags( );
    }

    const MicroLuaDebugTrace& MicroLuaContext::GetDebugTrace( ) const {
        return m_debugger.GetTrace( );
    }
#endif

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaContext::operator bool ( ) const {
    return GetIsValid( );
}

MicroLuaContext::operator lua_State* ( ) const {
    return GetState( );
}
