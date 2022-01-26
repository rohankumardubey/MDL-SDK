/***************************************************************************************************
 * Copyright (c) 2007-2022, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **************************************************************************************************/
/// \file
/// \brief Type that holds a reference to a database element.

#ifndef MI_NEURAYLIB_IREF_H
#define MI_NEURAYLIB_IREF_H

#include <mi/neuraylib/idata.h>

namespace mi {

/** \addtogroup mi_neuray_simple_types
@{
*/

/// A reference is an object that acts as a pointer to other database elements.
///
/// It can be used for example to store references to other database elements as an attribute
/// of a given database element.
class IRef :
    public base::Interface_declare<0x3572250a,0x605e,0x4b6c,0xa0,0xc3,0xae,0xd5,0x7e,0x24,0x69,0x9b,
                                   IData_simple>
{
public:
    /// Sets the reference to \p db_element.
    ///
    /// Note that a \c NULL pointer is a valid parameter value that clears the previously set
    /// reference. Subsequent #get_reference() calls will return \c NULL then.
    ///
    /// If a literal \c 0 is passed for \p db_element, the call is ambiguous. You need to explicitly
    /// cast the value to \c const \c IInterface* or \c const \c char*.
    ///
    /// \return
    ///           -  0: Success.
    ///           - -2: \p db_element does not point to a DB element.
    ///           - -3: \p db_element points to a DB element that has not yet been stored in the DB.
    ///           - -4: The reference can not be set to the element because the element is in a
    ///                 more private scope than the reference.
    virtual Sint32 set_reference( const base::IInterface* db_element) = 0;

    /// Sets the reference to the database element named \p name.
    ///
    /// Note that a \c NULL pointer is a valid parameter value that clears the previously set
    /// reference. Subsequent #get_reference() calls will return \c NULL then.
    ///
    /// If a literal \c 0 is passed for \p name, the call is ambiguous. You need to explicitly
    /// cast the value to \c const \c IInterface* or \c const \c char*.
    ///
    /// \return
    ///           -  0: Success.
    ///           - -2: There is no element with that name.
    ///           - -4: The reference can not be set to the element because the element is in a
    ///                 more private scope than the reference.
    virtual Sint32 set_reference( const char* name) = 0;

    /// Returns the reference.
    virtual const base::IInterface* get_reference() const = 0;

    /// Returns the reference.
    ///
    /// This templated member function is a wrapper of the non-template variant for the user's
    /// convenience. It eliminates the need to call
    /// #mi::base::IInterface::get_interface(const Uuid&)
    /// on the returned pointer, since the return type already is a pointer to the type \p T
    /// specified as template parameter.
    ///
    /// \tparam T     The requested interface type
    template <class T>
    const T* get_reference() const
    {
        const base::IInterface* ptr_iinterface = get_reference();
        if ( !ptr_iinterface)
            return 0;
        const T* ptr_T = static_cast<const T*>( ptr_iinterface->get_interface( typename T::IID()));
        ptr_iinterface->release();
        return ptr_T;
    }

    /// Returns the reference.
    virtual base::IInterface* get_reference() = 0;

    /// Returns the reference.
    ///
    /// This templated member function is a wrapper of the non-template variant for the user's
    /// convenience. It eliminates the need to call
    /// #mi::base::IInterface::get_interface(const Uuid&)
    /// on the returned pointer, since the return type already is a pointer to the type \p T
    /// specified as template parameter.
    ///
    /// \tparam T     The requested interface type
    template <class T>
    T* get_reference()
    {
        base::IInterface* ptr_iinterface = get_reference();
        if ( !ptr_iinterface)
            return 0;
        T* ptr_T = static_cast<T*>( ptr_iinterface->get_interface( typename T::IID()));
        ptr_iinterface->release();
        return ptr_T;
    }

    /// Returns the name of the referenced element.
    virtual const char* get_reference_name() const = 0;
};

/*@}*/ // end group mi_neuray_simple_types

} // namespace mi

#endif // MI_NEURAYLIB_IREF_H
