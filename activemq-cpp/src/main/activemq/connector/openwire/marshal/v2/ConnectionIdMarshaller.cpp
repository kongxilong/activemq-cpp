/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <activemq/connector/openwire/marshal/v2/ConnectionIdMarshaller.h>

#include <activemq/connector/openwire/commands/ConnectionId.h>

//
//     NOTE!: This file is autogenerated - do not modify!
//            if you need to make a change, please see the Java Classes in the
//            activemq-core module
//

using namespace std;
using namespace activemq;
using namespace activemq::io;
using namespace activemq::connector;
using namespace activemq::connector::openwire;
using namespace activemq::connector::openwire::commands;
using namespace activemq::connector::openwire::marshal;
using namespace activemq::connector::openwire::utils;
using namespace activemq::connector::openwire::marshal::v2;

///////////////////////////////////////////////////////////////////////////////
DataStructure* ConnectionIdMarshaller::createObject() const {
    return new ConnectionId();
}

///////////////////////////////////////////////////////////////////////////////
unsigned char ConnectionIdMarshaller::getDataStructureType() const {
    return ConnectionId::ID_CONNECTIONID;
}

///////////////////////////////////////////////////////////////////////////////
void ConnectionIdMarshaller::tightUnmarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataInputStream* dataIn, BooleanStream* bs ) throw( io::IOException ) {

    try {

        BaseDataStreamMarshaller::tightUnmarshal( wireFormat, dataStructure, dataIn, bs );

        ConnectionId* info =
            dynamic_cast<ConnectionId*>( dataStructure );
        info->setValue( tightUnmarshalString( dataIn, bs ) );
    }
    AMQ_CATCH_RETHROW( io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, io::IOException )
    AMQ_CATCHALL_THROW( io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
int ConnectionIdMarshaller::tightMarshal1( OpenWireFormat* wireFormat, DataStructure* dataStructure, BooleanStream* bs ) throw( io::IOException ) {

    try {

        ConnectionId* info =
            dynamic_cast<ConnectionId*>( dataStructure );

        int rc = BaseDataStreamMarshaller::tightMarshal1( wireFormat, dataStructure, bs );
        rc += tightMarshalString1( info->getValue(), bs );

        return rc + 0;
    }
    AMQ_CATCH_RETHROW( io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, io::IOException )
    AMQ_CATCHALL_THROW( io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
void ConnectionIdMarshaller::tightMarshal2( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataOutputStream* dataOut, BooleanStream* bs ) throw( io::IOException ) {

    try {

        BaseDataStreamMarshaller::tightMarshal2( wireFormat, dataStructure, dataOut, bs );

        ConnectionId* info =
            dynamic_cast<ConnectionId*>( dataStructure );
        tightMarshalString2( info->getValue(), dataOut, bs );
    }
    AMQ_CATCH_RETHROW( io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, io::IOException )
    AMQ_CATCHALL_THROW( io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
void ConnectionIdMarshaller::looseUnmarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataInputStream* dataIn ) throw( io::IOException ) {

    try {

        BaseDataStreamMarshaller::looseUnmarshal( wireFormat, dataStructure, dataIn );
        ConnectionId* info =
            dynamic_cast<ConnectionId*>( dataStructure );
        info->setValue( looseUnmarshalString( dataIn ) );
    }
    AMQ_CATCH_RETHROW( io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, io::IOException )
    AMQ_CATCHALL_THROW( io::IOException )
}

///////////////////////////////////////////////////////////////////////////////
void ConnectionIdMarshaller::looseMarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataOutputStream* dataOut ) throw( io::IOException ) {

    try {

        ConnectionId* info =
            dynamic_cast<ConnectionId*>( dataStructure );
         BaseDataStreamMarshaller::looseMarshal( wireFormat, dataStructure, dataOut );

        looseMarshalString( info->getValue(), dataOut );
    }
    AMQ_CATCH_RETHROW( io::IOException )
    AMQ_CATCH_EXCEPTION_CONVERT( exceptions::ActiveMQException, io::IOException )
    AMQ_CATCHALL_THROW( io::IOException )
}

