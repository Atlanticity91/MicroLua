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
MicroLuaDebugTrace::MicroLuaDebugTrace( )
	: StepMode{ false },
	Breakpoints{ } 
{ }

void MicroLuaDebugTrace::AddBreakpoint( const MicroLuaDebugBreakpoint& breakpoint ) {
	if ( Breakpoints.find( breakpoint.FileName ) == Breakpoints.end( ) ) {
		auto pair = std::make_pair( breakpoint.FileName, std::vector<uint32_t>{ 1 } );

		Breakpoints.emplace( std::move( pair ) );
	}

	Breakpoints[ breakpoint.FileName ].emplace_back( breakpoint.FileLine );
}

void MicroLuaDebugTrace::RemoveBreakpoint( const MicroLuaDebugBreakpoint& breakpoint ) {
	auto pair = Breakpoints.find( breakpoint.FileName );

	if ( pair != Breakpoints.end( ) ) {
		auto iterator_first = pair->second.begin( );
		auto iterator_last  = pair->second.end( );
		auto iterator		= std::find( iterator_first, iterator_last, breakpoint.FileLine );

		if ( iterator < pair->second.end( ) )
			pair->second.erase( iterator );
	}
}
