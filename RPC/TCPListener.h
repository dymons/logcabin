/* Copyright (c) 2011-2012 Stanford University
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR(S) DISCLAIM ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL AUTHORS BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef LOGCABIN_RPC_TCPLISTENER_H
#define LOGCABIN_RPC_TCPLISTENER_H

#include "Event/Loop.h"
#include "Address.h"

// forward declaration
namespace LibEvent {
class evconnlistener;
}

namespace LogCabin {
namespace RPC {

/**
 * A TCPListener listens for incoming TCP connections and accepts them.
 * The client should inherit from this and implement the handleNewConnection()
 * method for when a connection is accepted.
 *
 * TCPListeners can be created from any thread, but they will always run on
 * the thread running the Event::Loop.
 */
class TCPListener {
  public:

    /**
     * Constructor.
     * This will PANIC if it's not able to listen on the given address.
     * \param eventLoop
     *      Event::Loop that will manage this TCPListener object.
     * \param listenAddress
     *      The address to listen on.
     */
    explicit TCPListener(Event::Loop& eventLoop,
                         const Address& listenAddress);

    /**
     * Destructor.
     */
    virtual ~TCPListener();

    /**
     * This method is overridden by a subclass and invoked when a new
     * connection is accepted. This method will be invoked by the main event
     * loop on whatever thread is running the Event::Loop.
     *
     * The callee is in charge of closing the socket.
     */
    virtual void handleNewConnection(int socket) = 0;

    /**
     * Event::Loop that will manage this listener.
     */
    Event::Loop& eventLoop;

  private:

    /**
     * The address on which to listen.
     */
    Address listenAddress;

    /**
     * The listener from libevent.
     * This is never NULL.
     */
    LibEvent::evconnlistener* listener;

    // TCPListener is not copyable.
    TCPListener(const TCPListener&) = delete;
    TCPListener& operator=(const TCPListener&) = delete;
};

} // namespace LogCabin::RPC
} // namespace LogCabin

#endif /* LOGCABIN_RPC_TCPLISTENER_H */
