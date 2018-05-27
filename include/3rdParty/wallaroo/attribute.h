/*******************************************************************************
 * wallaroo - A library for configurable creation and wiring of C++ classes.
 * Copyright (C) 2012 Daniele Pallastrelli
 *
 * This file is part of wallaroo.
 * For more information, see http://wallaroolib.sourceforge.net/
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

#ifndef WALLAROO_ATTRIBUTE_H_
#define WALLAROO_ATTRIBUTE_H_

#include <string>
#include <sstream>
#include <iostream>
#include "cxx0x.h"
#include "part.h"
#include "deserializable_value.h"
#include "exceptions.h"


namespace wallaroo
{

namespace detail
{
    // Template function that converts a string into a value of type T
    // It provides a specialization to manage the case of type string

    // Generic conversion: try to convert v to type T and put the result in value
    // throw WrongType if v cannot be converted to T
    template < typename T >
    inline void String2Value( const std::string& v, T& value )
    {
        std::istringstream istream( v );
        if ( !( istream >> std::boolalpha >> value ) )
        {
            // error: didn't convert to T
            throw WrongType();
        }
    }

    // T is an unsigned char
    template <>
    inline void String2Value< unsigned char >( const std::string& v, unsigned char& value )
    {
        unsigned int x;
        String2Value( v, x );
        value = x;
    }

    // T is a string. No conversion needed
    template <>
    inline void String2Value< std::string >( const std::string& v, std::string& value )
    {
        value = v;
    }
}

/**
 * This is an attribute of a part. An attribute has a type T and
 * you can set its value at runtime by code or from a configuration file.
 *
 * You can put an Attribute inside your part and read its value and use
 * it as if it were of type T.
 *
 * @tparam T The type of the value contained
 */
template < typename T >
class Attribute : public DeserializableValue
{
public:

    /**
    * Create a Attribute and register it to its part so that you can
    * assign a value to it.
    * @param name the name of this attribute
    * @param token the registration token. You get an instance
    *              by calling Part::RegistrationToken()
    */
    Attribute( const std::string& name, const RegToken& token )
    {
        Part* owner = token.GetPart();
        owner -> Register( name, this );
    }

    /** Assign a value to the Attribute using a string as representation
     * @param v the string representation of the value
     * @throw WrongType if v cannot be converted to T
     */
    virtual void Value( const std::string& v )
    {
        detail::String2Value( v, value );
    }

    /** Conversion operator to the internal type @c T. Retrieve the internal value.
     *  Non const version.
     */
    operator T () { return value; }

    /** Conversion operator to the internal type @c T. Retrieve the internal value.
     *  Const version.
     */
    operator T () const { return value; }

    /** Conversion to C style string.
     *  It is available only when @c T is a @c std::string.
     *  @return the internal representation of the string as a C style const string
     */
    const char* c_str() const { return value.c_str(); }

    Attribute& operator = ( const Attribute& a ) { value = a.value;  return *this; }
    Attribute& operator = ( const T& v ) { value = v;  return *this; }

    Attribute& operator++( ) { ++value; return *this; }
    T operator++( int ) { T tmp( value ); operator++(); return tmp; }

    Attribute& operator--() { --value; return *this; }
    T operator--( int ) { T tmp( value ); operator--(); return tmp; }

    Attribute& operator+=( const T& rhs ) { value += rhs; return *this; }
    Attribute& operator-=( const T& rhs ) { value -= rhs; return *this; }
    Attribute& operator*=( const T& rhs ) { value *= rhs; return *this; }
    Attribute& operator/=( const T& rhs ) { value /= rhs; return *this; }

private:
    T value; // here we store the real attribute value

    // copy ctor disabled
    Attribute( const Attribute& );
};


// binary rel operators with lhs Attribute<T> and rhs T:

template < typename T > bool operator == ( const Attribute< T >& lhs, const T& rhs ) { return static_cast< T >( lhs ) == rhs; }
template < typename T > bool operator != ( const Attribute< T >& lhs, const T& rhs ) { return !operator==( lhs, rhs ); }

template < typename T > bool operator < ( const Attribute< T >& lhs, const T& rhs ){ return static_cast< T >( lhs ) < rhs; }
template < typename T > bool operator > ( const Attribute< T >& lhs, const T& rhs ){ return !operator<=( lhs, rhs ); }
template < typename T > bool operator <= ( const Attribute< T >& lhs, const T& rhs ){ return operator<( lhs, rhs ) || operator==( lhs, rhs ); }
template < typename T > bool operator >= ( const Attribute< T >& lhs, const T& rhs ){ return !operator<( lhs, rhs ); }


// binary rel operators with lhs T and rhs Attribute<T>:

template < typename T > bool operator == ( const T& lhs, const Attribute< T >& rhs ) { return operator==( rhs, lhs ); }
template < typename T > bool operator != ( const T& lhs, const Attribute< T >& rhs ) { return operator!=( rhs, lhs ); }

template < typename T > bool operator < ( const T& lhs, const Attribute< T >& rhs ){ return operator>( rhs, lhs ); }
template < typename T > bool operator > ( const T& lhs, const Attribute< T >& rhs ){ return operator<( rhs, lhs ); }
template < typename T > bool operator <= ( const T& lhs, const Attribute< T >& rhs ){ return !operator>( lhs, rhs ); }
template < typename T > bool operator >= ( const T& lhs, const Attribute< T >& rhs ){ return !operator<( lhs, rhs ); }

// concat operators
template < typename T > T operator + ( const Attribute< T >& lhs, const Attribute< T >& rhs ) { return static_cast< T >( lhs ) + static_cast< T >( rhs ); }
template < typename T > T operator + ( const Attribute< T >& lhs, const T& rhs ) { return static_cast< T >( lhs ) + rhs; }
template < typename T > T operator + ( const T& lhs, const Attribute< T >& rhs ) { return lhs + static_cast< T >( rhs ); }

// stream output operator
template < typename T >
std::ostream& operator << ( std::ostream& os, const Attribute< T >& att )
{ 
    os << static_cast< T >( att );
    return os;
}

}

#endif