/**
 *
 *  __  __ _            _
 * |  \/  (_)__ _ _ ___| |  _  _ __ _
 * | |\/| | / _| '_/ _ \ |_| || / _` |
 * |_|  |_|_\__|_| \___/____\_,_\__,_|
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

#pragma once

#include "MicroLuaMetatable.h"

template<typename Type, uint32_t FieldCount>
struct MicroLuaMetatableStorage {

	MicroLuaMetaField Fields[ micro_array_size<FieldCount> ];
	MicroLuaMetatable Detail;

	/**
	 * Constructor
	 * @param name : Query metatable name.
	 * @param lambda : Query construction lambda.
	 **/
	template<typename Lambda>
	MicroLuaMetatableStorage( micro_string name, Lambda&& lambda )
		: Detail{ name } 
	{
		std::invoke( lambda, this );

		Detail.FieldFirst = Fields;
		Detail.FieldLast  = ( Fields + FieldCount );
	};

	/**
	 * Cast operator
	 * @note : Get pointer to metatable detail.
	 * @return : Return pointer to Lua metatable detail.
	 **/
	operator MicroLuaMetatable* ( ) {
		return micro_ptr( Detail );
	};

};