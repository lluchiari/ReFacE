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

#ifndef WALLAROO_PART_H_
#define WALLAROO_PART_H_

#include <string>
#include <sstream>
#include "exceptions.h"
#include "cxx0x.h"
#include "dependency.h"
#include "deserializable_value.h"

namespace wallaroo
{

// forward declaration:
class Plugin;

/**
 * This class is a token used to ensure that Collaborators and Attributes 
 * can only be created as data members of Part.
 * The class carries also the part information.
 * This class should not be used directly: you can create an instace
 * by invoking the method Part::RegistrationToken() from a class
 * derived by Part.
 */
class RegToken
{
public:
    Part* GetPart() const { return part; }
private:
    friend class Part;
    RegToken( Part* d ) : part( d ) {}
    Part* part;
};

/**
 * This class represents a "part" that owns dependencies (collaborators) and
 * attributes.
 * You can link its dependencies to other parts using the method Part::Wire
 * and assign a value to its attributes using the method SetAttribute, but
 * wallaroo provides mechanisms more flexible for these tasks
 * (i.e., the DSL constructs "use().as().of()" and "set_attribute().of().to()" and the
 * configuration files).
 */
class Part
{
public:
    // we need to make Part virtual, to use dynamic_cast
    virtual ~Part() {}

    /** Link the dependency @c dependency of this part into the Part @c part.
     *  @throw ElementNotFound If @c dependency does not exist in this part.
     *  @throw WrongType If @c part has not a type compatible with the dependency.
     */
    void Wire( const std::string& dependency, const cxx0x::shared_ptr< Part >& part )
    {
        Dependencies::iterator i = dependencies.find( dependency );
        if ( i == dependencies.end() ) throw ElementNotFound( dependency );
        ( i -> second ) -> Link( part );
    }

    /** Assign a value to an attribute of the Part. 
     *  @param attribute The name of the attribute.
     *  @param value The value to assign.
     *  @throw ElementNotFound If @c attribute does not exist in this part.
     *  @throw WrongType If @c value has not a type compatible with the attribute.
     */
    // NOTE: we pass value as const reference to allow the effective specialization of string
    template < typename T >
    void SetAttribute( const std::string& attribute, const T& value )
    {
        std::ostringstream stream;
        if ( !( stream << std::boolalpha << value ) ) throw WrongType();
        SetStringAttribute( attribute, stream.str() );
    }

   /** Check the multiplicity of its collaborators.
    *  @return true If the check pass
    */
    bool MultiplicitiesOk() const
    {
        for ( 
            Dependencies::const_iterator i = dependencies.begin();
            i != dependencies.end();
            ++i
        )
            if ( ! i -> second -> WiringOk() )
                return false;
        return true;
    }

    /** This method get called by Catalog::Init().
     *  If you have work to be done for the initialization of your
     *  class, you should implement this method in the derived class.
     *  This is useful if you want to do your initialization after collaborators
     *  are been wired and attributes set. Keep in mind that in the constructor
     *  the wiring has not be performed yet.
     */
    virtual void Init() {};

protected:
    RegToken RegistrationToken()
    { 
        return RegToken( this );
    }
private:
    // this method should only be invoked by Class
    // to add the reference counter for the shared library.
    template < class T1, class T2 > friend class Class;
    void Source( const cxx0x::shared_ptr< Plugin >& p )
    {
        plugin = p;
    }

    // this method should only be invoked by the dependencies of this part
    // to register itself into the dependencies table.
    template < typename T, typename P, template < typename X > class Ownership >
    friend class Collaborator;
    void Register( const std::string& id, Dependency* c )
    {
        dependencies[ id ] = c;
    }

    // this method should only be invoked by the attributes of this part
    // to register itself into the attributes table.
    template < class T > friend class Attribute;
    void Register( const std::string& id, DeserializableValue* attribute )
    {
        attributes[ id ] = attribute;
    }

    // set attribute to a value represented as string.
    // throws ElementNotFound if the attribute doesn't exist.
    // throws WrongType if @c value is not a valid representation for the type of the attribute
    void SetStringAttribute( const std::string& attribute, const std::string& value )
    {
        Attributes::iterator i = attributes.find( attribute );
        if ( i == attributes.end() ) throw ElementNotFound( attribute );
        ( i -> second ) -> Value( value );
    }

    typedef cxx0x::unordered_map< std::string, Dependency* > Dependencies;
    Dependencies dependencies;

    typedef cxx0x::unordered_map< std::string, DeserializableValue* > Attributes;
    Attributes attributes;

    cxx0x::shared_ptr< Plugin > plugin; // optional shared ptr to plugin, to release the shared library when is no more used
};


/** Assign a value to a string attribute of the part.
 *  @param attribute The name of the attribute.
 *  @param value The value to assign.
 *  @throw ElementNotFound If @c attribute does not exist in this part.
 */
template <>
inline void Part::SetAttribute( const std::string& attribute, const std::string& value )
{
    // Optimization: with strings we don't need conversion
    SetStringAttribute( attribute, value );
}

} // namespace

#endif
