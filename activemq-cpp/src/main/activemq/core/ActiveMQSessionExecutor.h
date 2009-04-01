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

#ifndef ACTIVEMQ_CORE_ACTIVEMQSESSIONEXECUTOR_
#define ACTIVEMQ_CORE_ACTIVEMQSESSIONEXECUTOR_

#include <activemq/util/Config.h>
#include <activemq/core/Dispatcher.h>
#include <activemq/commands/ConsumerId.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/lang/Pointer.h>
#include <decaf/util/concurrent/Mutex.h>
#include <decaf/util/StlList.h>
#include <vector>
#include <list>

namespace activemq{
namespace core{

    using decaf::lang::Pointer;

    class ActiveMQSession;
    class ActiveMQConsumer;

    /**
     * Delegate dispatcher for a single session.  Contains a thread
     * to provide for asynchronous dispatching.
     */
    class AMQCPP_API ActiveMQSessionExecutor :
        public Dispatcher,
        public decaf::lang::Runnable
    {
    private:

        /** Session that is this executors parent. */
        ActiveMQSession* session;

        /** List used to hold messages waiting to be dispatched. */
        std::list<DispatchData> messageQueue;

        /** The Dispatcher Thread */
        Pointer<decaf::lang::Thread> thread;

        /** Mutex used to lock on access to the Message Queue */
        decaf::util::concurrent::Mutex mutex;

        /** Locks when messages are being dispatched to consumers. */
        decaf::util::concurrent::Mutex dispatchMutex;

        /** Has the Start method been called */
        volatile bool started;

        /** Has the Close method been called */
        volatile bool closed;

    public:

        /**
         * Creates an un-started executor for the given session.
         */
        ActiveMQSessionExecutor( ActiveMQSession* session );

        /**
         * Calls stop() then clear().
         */
        virtual ~ActiveMQSessionExecutor();

        /**
         * Executes the dispatch.  Adds the given data to the
         * end of the queue.
         * @param data - the data to be dispatched.
         */
        virtual void execute( DispatchData& data );

        /**
         * Executes the dispatch.  Adds the given data to the
         * beginning of the queue.
         * @param data - the data to be dispatched.
         */
        virtual void executeFirst( DispatchData& data );

        /**
         * Removes all messages for the given consumer from the.
         * @param consumerId - the subject consumer
         */
        virtual void purgeConsumerMessages(
            const decaf::lang::Pointer<commands::ConsumerId>& consumerId );

        /**
         * Starts the dispatching.
         */
        virtual void start();

        /**
         * Stops dispatching.
         */
        virtual void stop();

        /**
         * Terminates the dispatching thread.  Once this is called, the executor is no longer
         * usable.
         */
        virtual void close();

        /**
         * Indicates if the executor is started
         */
        virtual bool isStarted() const {
            return started;
        }

        /**
         * Removes all queued messages and destroys them.
         */
        virtual void clear();

        /**
         * Dispatches a message to a particular consumer.
         * @param consumer - The consumer to dispatch to.
         * @param msg - The message to be dispatched.
         */
        virtual void dispatch( DispatchData& data );

        /**
         * Run method - called by the Thread class in the context
         * of the thread.
         */
        virtual void run();

    private:

        /**
         * Dispatches all messages currently in the queue.
         */
        void dispatchAll();
    };

}}

#endif /*ACTIVEMQ_CORE_ACTIVEMQSESSIONEXECUTOR_*/