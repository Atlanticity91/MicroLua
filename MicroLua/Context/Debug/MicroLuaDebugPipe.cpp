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
//		===	INTERNAL ===
////////////////////////////////////////////////////////////////////////////////////////////
IMicroLuaDebugAdapter* MicroLuaDebugPipe::m_debug_adapter = nullptr;

bool GetAdapterIsValid( const IMicroLuaDebugAdapter* adapter ) {
	return adapter != nullptr && adapter->GetIsValid( );
}

void TerminateAdapter( IMicroLuaDebugAdapter*& adapter ) {
	if ( !GetAdapterIsValid( adapter ) )
		return;

	adapter->Disconnect( );

	adapter = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaDebugPipe::MicroLuaDebugPipe( ) 
{
#	ifdef MICRO_USE_CORE
	MicroDebugAdapter::Connect( { "127.0.0.1", 4000 } );
#	endif
}

MicroLuaDebugPipe::~MicroLuaDebugPipe( ) {
	TerminateAdapter( m_debug_adapter );

#	ifdef MICRO_USE_CORE
	MicroDebugAdapter::Disconnect( );
#	endif
}

bool MicroLuaDebugPipe::Attach( IMicroLuaDebugAdapter* adaptater ) {
	auto result = false;

	TerminateAdapter( m_debug_adapter );

	m_debug_adapter = adaptater;

	if ( m_debug_adapter != nullptr )
		result = m_debug_adapter->Connect( );

	return result;
}

bool MicroLuaDebugPipe::Broadcast( 
	const MicroLuaDebugAdapterBroadcastMessage* message
) {
	auto result = false;

	if ( message != nullptr ) {
		if ( GetAdapterIsValid( m_debug_adapter ) )
			result = m_debug_adapter->Broadcast( message );
#		ifdef MICRO_USE_CORE
		else {
			const auto* broadcast_message = micro_cast( message, const MicroDebugEvent* );

			result = ( MicroDebugAdapter::Broadcast( broadcast_message ) == MicroDebugAdapterError::None );
		}
#		endif
	}

	return result;
}

bool MicroLuaDebugPipe::Receive( MicroLuaDebugAdapterReceiveMessage& message ) {
	auto result = false;

	if ( message != nullptr ) {
		if ( GetAdapterIsValid( m_debug_adapter ) )
			result = m_debug_adapter->Receive( message );
#		ifdef MICRO_USE_CORE
		else {
			auto& debug_event = micro_ref_as( message, MicrDebugEventTypes );

			result = ( MicroDebugAdapter::Receive( debug_event ) == MicroDebugAdapterError::None );
		}
#		endif
	}

	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC STATIC GET ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaDebugPipe& MicroLuaDebugPipe::Get( ) {
	static auto instance = MicroLuaDebugPipe{ };

	return instance;
}
