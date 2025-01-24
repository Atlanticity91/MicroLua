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

#include "Debug/MicroLuaDebugger.h"

class MicroLuaContext final {

    friend class MicroLuaContextManager;

private:
    bool m_in_use;
    lua_State* m_state;
    std::vector<MicroLuaValue> m_returns;
    MicroLuaDebugger m_debugger;

public:
    MicroLuaContext( );

    MicroLuaContext( lua_State* lua_state );

    MicroLuaContext( const MicroLuaContext& other );
    
    MicroLuaContext( MicroLuaContext&& other ) noexcept;

    ~MicroLuaContext( );

    bool Create( );

    void SetDebugHook( lua_Hook lua_hook );
    void SetDebugHook( lua_Hook hook, const uint32_t flags );
    void AddDebugFlag( const uint32_t flags );
    void RemoveDebugFlag( const uint32_t flags );

    void AddBreakpoint( const MicroLuaDebugBreakpoint& breakpoint );
    void AddBreakpoint( const std::string& name, const uint32_t line );
    void RemoveBreakpoint( const MicroLuaDebugBreakpoint& breakpoint );
    void RemoveBreakpoint( const std::string& name, const uint32_t line );

    bool LoadDefaultLibraries( );
    bool LoadLibrary( lua_CFunction lua_library );
    bool LoadLibraries( std::initializer_list<lua_CFunction> libraries );

    bool Inject( const std::string lua_source );
    bool InjectFile( const std::string& file_path );

    bool Execute( const std::string& lua_source );

    void Terminate( );

public:
    template<typename Type>
    void Push( const std::string& name, const Type& value ) {
        if ( GetIsInUse( ) )
            return;

        auto* lua_name = name.c_str( );

        micro_compile_if( micro::GetCompileLuaType<Type> < MicroLuaTypes::Class )
            micro::lua_push( m_state, value );
        micro_compile_else{
            // TODO(Alves Quentin) : Manage metatable push.
        }

        lua_setglobal( m_state, lua_name );
    };

    template<>
    void Push( const std::string& name, const MicroLuaValue& value ) {
        if ( GetIsInUse( ) )
            return;

        auto* lua_name = name.c_str( );
        auto lua_value = value.GetData( );
        auto lua_type  = value.GetType( );

        switch ( lua_type ) {
            case MicroLuaTypes::Boolean  :
            case MicroLuaTypes::Integer  : lua_pushinteger( m_state, lua_value.Integer );                                break;
            case MicroLuaTypes::Number   : lua_pushnumber( m_state, lua_value.Number );                                  break;
            case MicroLuaTypes::String   : lua_pushstring( m_state, micro_cast( lua_value.Pointer, micro_string ) );     break;
            case MicroLuaTypes::Pointer  : lua_pushlightuserdata( m_state, lua_value.Pointer );                          break;
            case MicroLuaTypes::Function : lua_pushcfunction( m_state, micro_cast( lua_value.Pointer, lua_CFunction ) ); break;

            case MicroLuaTypes::Class : 
                /* TOOD( ALVES Quentin ) : Manage class */ 
                break;

            default : break;
        }

        lua_setglobal( m_state, lua_name );
    };

    template<>
    void Push<std::string>( 
        const std::string& name, 
        const std::string& value 
    ) {
        auto* lua_string = value.c_str( );

        Push( name, lua_string );
    };

    template<typename... Args>
    bool Invoke(
        const std::string& name,
        const uint32_t return_count, 
        Args&&... args 
    ) {
        auto result = false;

        if ( GetIsInUse( ) && !name.empty( ) ) {
            auto guard = MicroLuaStackGuard{ m_state };
            auto* functor = name.c_str( );

            lua_getglobal( m_state, functor );

            if ( lua_isfunction( m_state, MICRO_LUA_STACK_TOP ) ) {
                PushArguments<Args...>( std::forward<Args>( args )... );

                if ( result = lua_pcall( m_state, (uint32_t)sizeof...( Args ), return_count, 0 ) == LUA_OK )
                    AcquireReturn( return_count );
            }
        }

        return result;
    };

private:
    void Acquire( );

    void Release( );

    void AcquireReturn( uint32_t return_count );

private:
    template<typename... Args>
    void PushArguments( Args&&... args ) {
        micro_variadic_expand(
            micro_compile_if( micro::GetCompileLuaType<Args> < MicroLuaTypes::Class )
                micro::lua_push( m_state, args );
            micro_compile_else{
                // TODO(Alves Quentin) : Manage metatable parameter.
            }
        );
    };

public:
    bool GetIsValid( ) const;

    bool GetIsInUse( ) const;

    lua_State* GetState( ) const;

    MicroLuaDebugger& GetDebugger( );

    lua_Hook GetDebugHook( ) const;

    uint32_t GetDebugFlags( ) const;

    const MicroLuaDebugTrace& GetDebugTrace( ) const;

    MicroLuaValue Pop( const std::string& name );

    const std::vector<MicroLuaValue>& PopReturns( ) const;

public:
    template<typename Type>
    Type PopAs( const std::string& name ) {
        auto result = Pop( name );

        return result.As<Type>( );
    };

public:
    operator bool ( ) const;

    operator lua_State* ( ) const;

};
