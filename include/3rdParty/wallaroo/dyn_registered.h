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

 /**
 * @file
 * This header file must be included in *every* source file of a shared library.
 */
 
#ifndef WALLAROO_DYN_REGISTERED_H_
#define WALLAROO_DYN_REGISTERED_H_

#include "registered.h" // imports header with facilities to define wallaroo classes and WALLAROO_TOKENPASTE macro

// for the macro
#include "detail/dyn_class_descriptor.h"
#include "detail/dyn_class_descriptor_impl.h"

/** This macro must be used in the shared libraries
 * to register a class. When a class is registered, you can create an instance
 * using wallaroo::Catalog::Create().
 * Please note you can put multiple registration clauses, if you have multiple classes
 * defined in the same shared library.
 * @param C The class name
 * @hideinitializer
 */
#define WALLAROO_DYNLIB_REGISTER( C ) \
    static const ::wallaroo::detail::DynRegistration< C > WALLAROO_TOKENPASTE(__reg__,__LINE__)( #C ) ;


#endif // WALLAROO_DYN_REGISTERED_H_
