/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Reader.h"

#include <decaf/lang/Math.h>
#include <decaf/nio/CharBuffer.h>

#include <vector>

using namespace std;
using namespace decaf;
using namespace decaf::io;
using namespace decaf::lang;
using namespace decaf::lang::exceptions;
using namespace decaf::nio;

////////////////////////////////////////////////////////////////////////////////
Reader::Reader() {
}

////////////////////////////////////////////////////////////////////////////////
Reader::~Reader() {
}

////////////////////////////////////////////////////////////////////////////////
void Reader::mark( std::size_t readAheadLimit DECAF_UNUSED )
    throw( decaf::io::IOException ) {

    throw IOException(
        __FILE__, __LINE__,
        "Default implementation of Reader, mark not supported." );
}

////////////////////////////////////////////////////////////////////////////////
bool Reader::ready() const throw( decaf::io::IOException ) {
    return false;
}

////////////////////////////////////////////////////////////////////////////////
void Reader::reset() throw( decaf::io::IOException ) {

    throw IOException(
        __FILE__, __LINE__,
        "Default implementation of Reader, reset not supported." );
}

////////////////////////////////////////////////////////////////////////////////
std::size_t Reader::skip( std::size_t count )
    throw( decaf::io::IOException ) {

    try{

        std::size_t skipped = 0;
        int toRead = count < 512 ? (int)count : 512;

        std::vector<char> charsSkipped( toRead );

        while( skipped < count ) {

            int read = this->read( &charsSkipped[0], 0, toRead );
            if( read == -1 ) {
                return skipped;
            }
            skipped += read;
            if( read < toRead ) {
                return skipped;
            }
            if( count - skipped < (std::size_t)toRead ) {
                toRead = (int)( count - skipped );
            }
        }

        return skipped;
    }
    DECAF_CATCH_RETHROW( IOException )
    DECAF_CATCHALL_THROW( IOException )
}

////////////////////////////////////////////////////////////////////////////////
int Reader::read( std::vector<char>& buffer ) throw( decaf::io::IOException ) {

    try{

        if( buffer.size() == 0 ) {
            return -1;
        }

        return this->read( &buffer[0], 0, buffer.size() );
    }
    DECAF_CATCH_RETHROW( IOException )
    DECAF_CATCHALL_THROW( IOException )
}

////////////////////////////////////////////////////////////////////////////////
int Reader::read() throw( IOException ) {

    try{
        char buffer;

        if( this->read( &buffer, 0, 1 ) == -1 ) {
            return -1;
        }

        return buffer;
    }
    DECAF_CATCH_RETHROW( IOException )
    DECAF_CATCHALL_THROW( IOException )
}

////////////////////////////////////////////////////////////////////////////////
int Reader::read( decaf::nio::CharBuffer* charBuffer )
         throw( decaf::io::IOException,
                decaf::lang::exceptions::NullPointerException,
                decaf::nio::ReadOnlyBufferException ) {

    try{

        if( charBuffer == NULL ) {
            throw NullPointerException(
                __FILE__, __LINE__, "Pointer to CharBuffer cannot be NULL." );
        }

        if( charBuffer->length() == 0 ) {
            return 0;
        }

        int length = (int)charBuffer->length();

        std::vector<char> buffer( length );

        length = Math::min( length, this->read( buffer ) );

        if( length > 0 ) {
            charBuffer->put( &buffer[0], 0, length );
        }

        return length;
    }
    DECAF_CATCH_RETHROW( IOException )
    DECAF_CATCH_RETHROW( NullPointerException )
    DECAF_CATCH_RETHROW( ReadOnlyBufferException )
    DECAF_CATCHALL_THROW( IOException )
}
