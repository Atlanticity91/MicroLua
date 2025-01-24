/**
 *
 *  __  __ _           _____       _
 * |  \/  (_)__ _ _ __|_   _|__ __| |_
 * | |\/| | / _| '_/ _ \| |/ -_|_-<  _|
 * |_|  |_|_\__|_| \___/|_|\___/__/\__|
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

#include "MicroTest_LuaToString.h"

////////////////////////////////////////////////////////////////////////////////////////////
//		===	TEST ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace UnitTest {

	TEST_CLASS( MicroTest_LuaDebug ) {

	private:
		MicroLuaContext CreateTestContext( 
			std::initializer_list<lua_CFunction> libraries 
		) {
			auto context = MicroLuaContext{ };

			Assert::IsTrue( context.Create( ) );

			context.LoadLibraries( libraries );

			return std::move( context );
		};

	public:
		TEST_METHOD( Breakpoint ) {
			auto context = CreateTestContext( { } );
			
			context.Inject( "function m( a )\nprint( a )\nend\n" );
			context.AddBreakpoint( { "", 2 } );
			context.Invoke( "m", 0, 10 );

			const auto& debug_trace = context.GetDebugTrace( );

			Assert::IsTrue( debug_trace.HasStopped );
		};

	};

};
