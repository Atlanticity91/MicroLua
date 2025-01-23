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
//		===	PUBLIC STATIC ===
////////////////////////////////////////////////////////////////////////////////////////////
SOCKET MicroLuaDebugPipe::m_socket = INVALID_SOCKET;

MicroLuaDebugPipeErrors MicroLuaDebugPipe::Create( 
    const MicroLuaDebugPipeSpecificaton& specification 
) {
    auto result = MicroLuaDebugPipeErrors::None;

#   ifdef _MSC_VER
    auto wsa_data = WSADATA{ };

    if ( WSAStartup( MAKEWORD( 2, 2 ), micro_ptr( wsa_data ) ) == 0 ) {
        m_socket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

        if ( m_socket != INVALID_SOCKET ) {
            auto socket_address = sockaddr_in{ };

            socket_address.sin_family = AF_INET;
            socket_address.sin_port = htons( specification.Port );
            socket_address.sin_addr.s_addr = inet_addr( specification.Address );

            if ( connect( m_socket, micro_ptr_as( socket_address, sockaddr* ), sizeof( sockaddr_in ) ) < 0 ) {
                closesocket( m_socket );
                WSACleanup( );

                result = MicroLuaDebugPipeErrors::SocketConnectionFail;
            }
        } else {
            WSACleanup( );

            result = MicroLuaDebugPipeErrors::SocketCreationFail;
        }
    } else 
        result = MicroLuaDebugPipeErrors::SocketInitFail;

#   endif

    return result;
}

void MicroLuaDebugPipe::Write( const std::string& message ) {
#   ifdef _MSC_VER
    if ( m_socket == INVALID_SOCKET )
        return;

    auto* message_value = message.c_str( );
    auto message_length = (uint32_t)message.length( );

    send( m_socket, message_value, message_length, 0 );
#   endif
}

bool MicroLuaDebugPipe::Read( char* buffer, const uint32_t length ) {
    auto result = false;

#   ifdef _MSC_VER
    if ( m_socket != INVALID_SOCKET ) {
        auto receive_length = recv( m_socket, buffer, length * micro_sizeof( char ), 0 );

        if ( receive_length > 0 )
            result = ( receive_length <= length );
    }
#   endif

    return result;
}

MicroLuaDebugPipeErrors MicroLuaDebugPipe::Terminate( ) {
    auto result = MicroLuaDebugPipeErrors::None;

#   ifdef _MSC_VER
    if ( m_socket != INVALID_SOCKET ) {
        if ( shutdown( m_socket, SD_BOTH ) != SOCKET_ERROR ) {
            if ( closesocket( m_socket ) == SOCKET_ERROR )
                result = MicroLuaDebugPipeErrors::SocketCloseFail;
        } else 
            result = MicroLuaDebugPipeErrors::SocketShutdownFail;

        WSACleanup( );
    }
#   endif

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC STATIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
bool MicroLuaDebugPipe::GetIsValid( ) {
    return  m_socket != INVALID_SOCKET;
}
