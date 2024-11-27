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

#include <__micro_lua_pch.h>

#ifdef MICRO_USE_CORE
////////////////////////////////////////////////////////////////////////////////////////////
//		===	PUBLIC ===
////////////////////////////////////////////////////////////////////////////////////////////
MicroLuaGenerator::MicroLuaGenerator( )
	: MicroReflectEmitter{ }
{ }

void MicroLuaGenerator::PreRun( MicroReflectSourceDeclaration& declaration ) {
}

void MicroLuaGenerator::Run( const MicroReflectSourceDeclaration& declaration ) {
	auto dst_path = declaration.Source;

	dst_path.replace_extension( ".lua.h" );

	auto file = std::ofstream{ dst_path };

	file << "/**\n";
	file << " *\n";
	file << " *  __  __ _            ___      __ _        _\n";
	file << " * |  \\/  (_)__ _ _ ___| _ \\___ / _| |___ __| |_\n";
	file << " * | |\\/| | / _| '_/ _ \\   / -_)  _| / -_) _|  _|\n";
	file << " * |_|  |_|_\\__|_| \\___/_|_\\___|_| |_\\___\\__|\\__|\n";
	file << " *\n";
	file << " * Do not edit or delete.\n";
	file << " * This file was automatically generated by MicroLuaGenerator.\n";
	file << " * Contain lua interoperation implementation for types found in\n";
	file << " * source file : " << declaration.Source << "\n";
	file << " *\n";
	file << " **/\n\n";
	file << "#pragma once\n\n";
	file << "namespace micro {\n";
	file << "};\n";

	file.close( );
}

#endif
