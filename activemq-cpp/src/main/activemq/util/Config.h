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
#ifndef ACTIVEMQ_UTIL_CONFIG_H_
#define ACTIVEMQ_UTIL_CONFIG_H_

//
// The purpose of this header is to try to detect the supported headers 
// of the platform when the ./configure script is not being used to generate
// the config.h file.
//
#if defined(HAVE_CONFIG_H) 

	// config.h is generated by the ./configure script and it only 
	// used by unix like systems (including cygwin)
	#include <config.h>

#else /* !defined(HAVE_CONFIG_H) */

	// Not using ./configure script and make system.. chances are your using the native build tools
	// of Windows or OS X to do this build
    
	#if defined(_WIN32)
        #ifndef HAVE_OBJBASE_H
		    #define HAVE_OBJBASE_H
        #endif
        #ifndef HAVE_RPCDCE_H
		    #define HAVE_RPCDCE_H
        #endif
        #ifndef HAVE_WINSOCK2_H
		    #define HAVE_WINSOCK2_H
        #endif
        #ifndef HAVE_STRUCT_ADDRINFO
            #define HAVE_STRUCT_ADDRINFO
        #endif
        #ifndef HAVE_SYS_TIMEB_H
            #define HAVE_SYS_TIMEB_H
        #endif
        #ifndef HAVE_FTIME
            #define HAVE_FTIME
        #endif
        #ifndef HAVE_WINDOWS_H
            #define HAVE_WINDOWS_H
        #endif
	#else
        #ifndef HAVE_UUID_UUID_H
		    #define HAVE_UUID_UUID_H
        #endif
        #ifndef HAVE_UUID_T
            #define HAVE_UUID_T
        #endif
        #ifndef HAVE_PTHREAD_H
            #define HAVE_PTHREAD_H
        #endif
	#endif

#endif /* !defined(HAVE_CONFIG_H) */

// Macro to mark attributes as unused
#ifdef __GNUC__
   #define AMQCPP_UNUSED __attribute__ ((__unused__))
#else
   #define AMQCPP_UNUSED
#endif


#endif /*ACTIVEMQ_UTIL_CONFIG_H_*/
