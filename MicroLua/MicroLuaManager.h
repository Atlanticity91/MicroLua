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

#include "Registry/MicroLuaRegistry.h"

/**
 * @class MicroLuaManager
 * @brief Lua manager to encapsulate preprocessing lua script, manage registry
 *        for Lua-C++ shared globals and Lua context for executing Lua on 
 *        multiple trhead with multiple Lua state.
 * @field m_preprocessor Current manager lua preprocessor instance.
 * @field m_registry Current manager lua registry instance.
 * @field m_context Current manager lua context manager instance.
 **/
class MicroLuaManager final {

private:
    std::mutex m_thread_locker;
    MicroLuaPreprocessor m_preprocessor;
    MicroLuaRegistry m_registry;
    MicroLuaContextManager m_context;

public:
    /**
     * @brief Create and initialize a Lua manager instance.
     **/
    MicroLuaManager( );

    /**
     * @brief Terminate and clean up the Lua manager instance.
     * @note call Terminate( ) if it is not called manually.
     **/
    ~MicroLuaManager( );

    /**
     * @brief Create all Lua state required for the specified 
     *        numbers of threads.
     * @param[in] context_count The number of thread or number ot Lua context to
     *            create, default is 1.
     * @return true if all Lua contexts were created successfully; false otherwise.
     **/
    bool Create( const uint32_t context_count = 1 );

    bool Add( const std::string& name, const MicroLuaLibraryNative& library );

    bool Add( const std::string& name, const MicroLuaLibraryManaged& library );

    bool Extend( const std::string& name, const MicroLuaLibraryNative& extension );

    bool Remove( const std::string& name );

    bool Enable( const std::string& name );

    bool Disable( const std::string& name );
    
    /**
     * @brief Unregister the value associated with the given name from the 
     *        registry.
     * @param[in] name The name of the registry value to remove.
     * @return true when the deletion was successful; false otherwise.
     **/
    bool UnRegister( const std::string& name );

    /**
     * @brief Acquire a free Lua context handle.
     * @return a valid Lua context handle if successful; an invalid handle 
     *         value otherwise.
     **/
    uint32_t Acquire( );

    /**
     * @brief Release the Lua context associated with provided context handle.
     * @param[in] context_handle The context handle of the Lua context to release.
     **/
    void Release( uint32_t& context_handle );

    /**
     * @brief Terminates and cleans up the Lua manager instance.
     **/
    void Terminate( );

public:
    /**
     * @brief Register the provided value with the associated name in the registry.
     * @template[in] Type The C++ type of the provided value.
     * @param[in] name The name under which the value will be registered in the 
     *            registry.
     * @param[in] value The C++ value to register.
     * @return true if the provided value was successfully registered under the 
     *         specified name in the registry; false otherwise.
     **/
    template<typename Type>
    bool Register( const std::string& name, const Type& value ) {
        return m_registry.Register<Type>( name, value );
    };

public:
    /**
     * @brief Get if a value in the registry exist under the specified name.
     * @param[in] name The name to look for in the registry.
     * @return true if a value exists under the specified name in the registry; 
     *         false otherwise.
     **/
    bool GetGlobalExist( const std::string& name ) const;

    /**
     * @brief Retrieve the value under provided name from the registry.
     * @param[in] name The name of the value in the registry.
     * @return the value under name, or a default-initialized MicroLuaValue if 
     *         not found.
     **/
    MicroLuaValue GetGlobal( const std::string& name ) const;

    bool GetLibraryExist( const std::string& name ) const;

    bool GetIsLibraryEnabled( const std::string& name ) const;

    bool GetIsLibraryManaged( const std::string& name ) const;

    /**
     * @brief Verify if a context handle value is valid.
     * @param[in] context_handle The context handle value to verify.
     * @return true if the context handle points to a valid Lua context; false 
     *         otherwise.
     **/
    bool GetContextExist( const uint32_t context_handle ) const;

    /**
     * @brief Retrieve the Lua context assotiated with the provided context 
     *        handle.
     * @param[in] context_handle The context handle value.
     * @return a pointer to the Lua context associated with the provided context 
     *         handle, or nullptr if not found.
     **/
    MicroLuaContext* GetContext( const uint32_t context_handle );

public:
    /**
     * @brief Retrieve the value under provided name from the registry, casted to 
     *        the specified type.
     * @template[in] Type The C++ type to cast the value to.
     * @param[in] name The name of the value in the registry.
     * @return the value cast to the specified type, or a default-initialized 
     *         value of Type if not found.
     **/
    template<typename Type>
    Type Get( const std::string& name ) const {
        auto value = m_registry.GetGlobal( name );

        return value.As<Type>( );
    };

public:
    /**
     * @brief Retrieves the Lua context associated with the provided context handle.
     * @param[in] context_handle The context handle value.
     * @return a pointer to the Lua context associated with the provided context 
     *         handle, or nullptr if not found.
     **/
    MicroLuaContext* operator[]( const uint32_t context_handle );

};
