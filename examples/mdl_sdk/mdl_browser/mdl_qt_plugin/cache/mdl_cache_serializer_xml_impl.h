/******************************************************************************
 * Copyright (c) 2018-2022, NVIDIA CORPORATION. All rights reserved.
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
 *****************************************************************************/

/// \file
/// \brief Implementation of the IMdl_cache_serializer_xml interface.


#ifndef MDL_SDK_EXAMPLES_MDL_BROWSER_MDL_CACHE_SERIALIZER_XML_IMPL_H
#define MDL_SDK_EXAMPLES_MDL_BROWSER_MDL_CACHE_SERIALIZER_XML_IMPL_H

#include "imdl_cache.h"

namespace tinyxml2 {
    class XMLElement;
}

class Mdl_cache_serializer_xml_impl : public IMdl_cache_serializer_xml
{
public:
    explicit Mdl_cache_serializer_xml_impl();
    virtual ~Mdl_cache_serializer_xml_impl() = default;

    bool serialize(const IMdl_cache* cache, const char* file_path) const override;
    IMdl_cache_package* deserialize(IMdl_cache* cache, const char* file_path) const override;


protected:
     virtual tinyxml2::XMLElement* serialize(tinyxml2::XMLElement* parent, 
                                             const IMdl_cache_item* item) const;

     virtual IMdl_cache_item* deserialize(IMdl_cache* cache, 
                                          const IMdl_cache_node* parent, 
                                          const tinyxml2::XMLElement* item) const;
};

#endif