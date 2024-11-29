/**
 * 
 *  __  __ _           _____       _ 
 * |  \/  (_)__ _ _ __|_   _|__ __| |_
 * | |\/| | / _| '_/ _ \| |/ -_|_-<  _|
 * |_|  |_|_\__|_| \___/|_|\___/__/\__|
 *
 * MIT License
 *
 * Copyright (c) 2024 Alves Quentin
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

#include "CppUnitTest.h"
#include <MicroLua.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework {

	/**
	 * ToString function
	 * @note : Convert Lua types to string.
	 * @param value : Query Lua type.
	 * @return : Return Lua type string value.
	 **/
	template<> 
	inline std::wstring ToString<MicroLuaTypes>( const MicroLuaTypes& value ) { 
		auto result = std::wstringstream{ };

		switch ( value ) {
			case MicroLuaTypes::Boolean  : result << "Boolean";  break;
			case MicroLuaTypes::Integer  : result << "Integer";  break;
			case MicroLuaTypes::Number   : result << "Number";   break;
			case MicroLuaTypes::Pointer  : result << "Pointer";  break;
			case MicroLuaTypes::Function : result << "Function"; break;
			case MicroLuaTypes::Class	 : result << "Class";	 break;
			case MicroLuaTypes::None	 : result << "None";	 break;

			default : break;
		}

		return result.str( );
	}

};

////////////////////////////////////////////////////////////////////////////////////////////
//		===	TEST ===
////////////////////////////////////////////////////////////////////////////////////////////
namespace UnitTest {

	TEST_CLASS( MicroLuaInteroperation ) {

		struct TestType { };

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

		TEST_METHOD( Call ) { 
			auto context = CreateTestContext( { } );
			
			context.LoadDefaultLibraries( );
			context.Inject( "function m( a )\nprint( a )\nend\n" );

			Assert::IsTrue( context.Call( "m", 10 ) );
		};

		TEST_METHOD( CallParams ) {
			auto context = CreateTestContext( { } );

			context.LoadDefaultLibraries( );
			context.Inject( "function add( a, b )\nreturn a + b\nend\n" );
			
			Assert::AreEqual( 9, context.CallFunction<int>( "add", 5, 4 ) );
		};

		TEST_METHOD( GetAs ) {
			auto context = CreateTestContext( { } );

			context.Inject( "x = 10 * 4" );

			Assert::AreEqual( 40, context.GetAs<int32_t>( "x" ) );
		};

		TEST_METHOD( Class ) {
			auto context = CreateTestContext( { } );

			context.LoadDefaultLibraries( );
			context.Inject( "l = { }" );

			Assert::IsTrue( MicroLuaClass{ context, "l" } );

			auto k = context.GetAs<MicroLuaClass>( "l" );

			Assert::IsTrue( k );
		};

		TEST_METHOD( ClassSet ) {
			auto context = CreateTestContext( { } );

			context.LoadDefaultLibraries( );
			context.Inject( "l = { a = 10, b = \"Test\" }" );



			auto lua_class = MicroLuaClass{ context, "l" };

			Assert::AreEqual( MicroLuaTypes::String, lua_class.GetHas( context, "b" ) );
			Assert::IsTrue( lua_class.Set( context, "a", 40 ) );
			Assert::IsTrue( lua_class.Set( context, "b", "No" ) );
			Assert::AreEqual( 40, lua_class.Get( context, "a" ).As<int>( ) );
			Assert::AreEqual( "No", lua_class.GetAs<micro_string>( context, "b" ) );
		};

		TEST_METHOD( ClassGet ) {
			auto context = CreateTestContext( { } );

			context.LoadDefaultLibraries( );
			context.Inject( "l = { a = 10, b = \"Test\" }" );

			auto lua_class = MicroLuaClass{ context, "l" };

			Assert::IsTrue( lua_class.GetHasField( context, "a" ) );
			Assert::IsTrue( lua_class.GetHasField( context, "b" ) );
		};

	};

};
