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

#include "MicroLuaMetaField.h"

#define MICRO_REFLECT_LUA( )\
	template<class T>\
	friend micro::MicroLuaMetatable* micro::GetLuaMetatable( ) noexcept;

/**
 * MicroLuaMetatable struct
 * @note : Represent Lua metatable.
 **/
micro_struct MicroLuaMetatable {

	micro_string Name;
	MicroLuaMetaField* FieldFirst;
	MicroLuaMetaField* FieldLast;

	/**
	 * Constructor
	 * @param name : Query metatable name.
	 **/
	MicroLuaMetatable( micro_string name );

	/**
	 * GetCount const function
	 * @note : Get field count.
	 * @return : Return field count value.
	 **/
	uint32_t GetCount( ) const;

	/**
	 * begin function
	 * @note : Get first element.
	 * @return : Return first element value.
	 **/
	MicroLuaMetaField* begin( );

	/**
	 * end function
	 * @note : Get end element.
	 * @return : Return end element value.
	 **/
	MicroLuaMetaField* end( );

};

namespace micro {

	/**
	 * GetLuaMetatable function
	 * @note : Get metatable instance of type T.
	 * @template T : Query type.
	 * @return : Return metatable of T.
	 **/
	template<class T>
	const MicroLuaMetatable* GetLuaMetatable( ) noexcept {
		return nullptr;
	};

};
