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

	TEST_CLASS( MicroTest_LuaTypes ) {

		struct TestType { };

	public:
		TEST_METHOD( GetLuaType ) {
			Assert::AreEqual( MicroLuaTypes::Integer , micro::GetLuaType<lua_Integer>( ) );
			Assert::AreEqual( MicroLuaTypes::Number  , micro::GetLuaType<lua_Number>( ) );
			Assert::AreEqual( MicroLuaTypes::Function, micro::GetLuaType<lua_CFunction>( ) );
			Assert::AreEqual( MicroLuaTypes::Boolean , micro::GetLuaType<bool>( ) );
			Assert::AreEqual( MicroLuaTypes::Pointer , micro::GetLuaType<void*>( ) );
			Assert::AreEqual( MicroLuaTypes::Pointer , micro::GetLuaType<TestType*>( ) );
			Assert::AreEqual( MicroLuaTypes::Class	 , micro::GetLuaType<TestType>( ) );
			Assert::AreEqual( MicroLuaTypes::String  , micro::GetLuaType<micro_string>( ) );
			Assert::AreEqual( MicroLuaTypes::String  , micro::GetLuaType<std::string>( ) );
		};

	};

};
