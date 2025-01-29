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

#define MICRO_TRACE_NAME "__micro_trace"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaDebugger::MicroLuaDebugger( )
    : m_hook{ },
    m_flags{ },
    m_trace{ }
{ 
    Reset( );
}

void MicroLuaDebugger::Set( lua_Hook hook ) {
    m_hook = hook;
}

void MicroLuaDebugger::Set( lua_Hook hook, const uint32_t flags ) {
    m_hook  = hook;
    m_flags = flags;
}

void MicroLuaDebugger::Reset( ) {
    m_hook  = &MicroLuaDebugger::DebugHook;
    m_flags = LUA_MASKCALL | LUA_MASKRET | LUA_MASKLINE;
}

void MicroLuaDebugger::Add( const uint32_t flags ) {
    m_flags |= flags;
}

void MicroLuaDebugger::Remove( const uint32_t flags ) {
    m_flags &= flags;
}

void MicroLuaDebugger::AddBreakpoint( const MicroLuaDebugBreakpoint& breakpoint ) {
    m_trace.AddBreakpoint( breakpoint );
}

void MicroLuaDebugger::AddBreakpoint( const uint32_t line ) {
    m_trace.AddBreakpoint( { "", line } );
}

void MicroLuaDebugger::AddBreakpoint( const std::string& name, const uint32_t line ) {
    m_trace.AddBreakpoint( { name, line } );
}

void MicroLuaDebugger::RemoveBreakpoint( const MicroLuaDebugBreakpoint& breakpoint ) {
    m_trace.AddBreakpoint( breakpoint );
}

void MicroLuaDebugger::RemoveBreakpoint( const uint32_t line ) {
    m_trace.AddBreakpoint( { "", line } );
}

void MicroLuaDebugger::RemoveBreakpoint( const std::string& name, const uint32_t line ) {
    m_trace.AddBreakpoint( { name, line } );
}

void MicroLuaDebugger::Enable( lua_State* lua_state ) {
    lua_pushlightuserdata( lua_state, micro_ptr_as( m_trace, void* ) );
    lua_setglobal( lua_state, MICRO_TRACE_NAME );

    lua_sethook( lua_state, m_hook, m_flags, 0 );
}

void MicroLuaDebugger::Disable( lua_State* lua_state ) {
    lua_sethook( lua_state, NULL, 0, 0 );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaDebugger::GetHookIsBreakpoint(
    lua_Debug* lua_debug,
    MicroLuaDebugTrace* trace
) {
    auto result = false;
    auto name   = std::string{ lua_debug->name ? lua_debug->name : "" };
    auto pair   = trace->Breakpoints.find( name );

    if ( pair != trace->Breakpoints.end( ) ) {
        for ( const auto& line : pair->second ) {
            if ( result = ( line == lua_debug->currentline ) )
                break;
        }
    }

    return result;
}

void MicroLuaDebugger::SendHookMessage( 
    lua_Debug* lua_debug,
    MicroLuaDebugTrace* trace
) {
    /*
    auto break_point = MicroDebugEventBreakpoint{ 0 };
    
    break_point.Line   = lua_debug->currentline;
    break_point.Source = lua_debug->source;

    MicroLuaDebugPipe::Broadcast( &break_point );
    */
    trace->HasStopped = true;
}

void MicroLuaDebugger::ParseHookResponse( MicroLuaDebugTrace* trace ) {
    /*
    auto server_command = (uint32_t)0;
    if ( MicroLuaDebugPipe::Receive( server_command ) ) { 
        auto buffer_string = std::string{ buffer };

        if ( buffer_string.find( "\"command\":\"continue\"" ) != std::string::npos ) {
            trace->HasStopped = false;
            trace->StepMode   = false;
        } else if ( buffer_string.find( "\"command\":\"step\"" ) != std::string::npos )
            trace->StepMode = true;
    }
    */
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PRIVATE STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
void MicroLuaDebugger::DebugHook( lua_State* lua_state, lua_Debug* lua_debug ) {
    lua_getglobal( lua_state, MICRO_TRACE_NAME );
    auto* lua_trace = micro_cast( lua_touserdata( lua_state, MICRO_LUA_STACK_TOP ), MicroLuaDebugTrace* );
    lua_pop( lua_state, 1 );

    if ( lua_trace == NULL || !lua_trace->GetIsValid( ) )
        return;

    lua_getstack( lua_state, 0, lua_debug );
    lua_getinfo( lua_state, "nSlu", lua_debug );

    if ( !GetHookIsBreakpoint( lua_debug, lua_trace ) )
        return;

    SendHookMessage( lua_debug, lua_trace );
    ParseHookResponse( lua_trace );
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
lua_Hook MicroLuaDebugger::GetHook( ) const {
    return m_hook;
}

uint32_t MicroLuaDebugger::GetFlags( ) const {
    return m_flags;
}

const MicroLuaDebugTrace& MicroLuaDebugger::GetTrace( ) const { 
    return m_trace;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	OPERATOR ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaDebugger& MicroLuaDebugger::operator=( const MicroLuaDebugger& other ) {
    m_hook  = other.m_hook;
    m_flags = other.m_flags;
    m_trace = other.m_trace;

    return micro_self;
}

MicroLuaDebugger& MicroLuaDebugger::operator=( MicroLuaDebugger&& other ) noexcept {
    m_hook  = other.m_hook;
    m_flags = other.m_flags;
    m_trace = std::move( other.m_trace );

    return micro_self;
}
