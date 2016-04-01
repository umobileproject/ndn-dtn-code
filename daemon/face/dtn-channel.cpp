/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014-2015,  Regents of the University of California,
 *                           Arizona Board of Regents,
 *                           Colorado State University,
 *                           University Pierre & Marie Curie, Sorbonne University,
 *                           Washington University in St. Louis,
 *                           Beijing Institute of Technology,
 *                           The University of Memphis.
 *
 * This file is part of NFD (Named Data Networking Forwarding Daemon).
 * See AUTHORS.md for complete list of NFD authors and contributors.
 *
 * NFD is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * NFD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * NFD, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "dtn-channel.hpp"
//#include "generic-link-service.hpp"
//#include "unix-stream-transport.hpp"
//#include "core/global-io.hpp"

//#include <boost/filesystem.hpp>
#include <sys/stat.h> // for chmod()

namespace nfd {

NFD_LOG_INIT("DtnChannel");

//DtnChannel::DtnChannel()
DtnChannel::DtnChannel(const dtn::Endpoint& endpoint, uint16_t port)
  : m_endpoint(endpoint)
  , m_port(port)
{
  m_is_open = false;
  setUri(FaceUri(m_endpoint, m_port));
}

DtnChannel::~DtnChannel()
{
  if (isListening()) {
    // use the non-throwing variants during destruction
    // and ignore any errors
    //boost::system::error_code error;
    //m_acceptor.close(error);
    NFD_LOG_DEBUG(" Removing dtn socket");
    m_is_open = false;
    //boost::filesystem::remove(m_endpoint.path(), error);
  }
}

void
DtnChannel::listen(const FaceCreatedCallback& onFaceCreated,
                          const FaceCreationFailedCallback& onAcceptFailed)
                          //int backlog/* = acceptor::max_connections*/)
{
  if (isListening()) {
    NFD_LOG_WARN("[" << m_endpoint << "] Already listening");
    return;
  }
  m_is_open = true;

  //m_acceptor.open();
  //m_acceptor.bind(m_endpoint);
  //m_acceptor.listen(backlog);

  // start accepting connections
  accept(onFaceCreated, onAcceptFailed);
}

void
DtnChannel::accept(const FaceCreatedCallback& onFaceCreated,
                          const FaceCreationFailedCallback& onAcceptFailed)
{
  /*m_acceptor.async_accept(m_socket, bind(&DtnChannel::handleAccept, this,
                                         boost::asio::placeholders::error,
                                         onFaceCreated, onAcceptFailed));*/
}

void
DtnChannel::handleAccept(const boost::system::error_code& error,
                                const FaceCreatedCallback& onFaceCreated,
                                const FaceCreationFailedCallback& onAcceptFailed)
{
  if (error) {
    if (error == boost::asio::error::operation_aborted) // when the socket is closed by someone
      return;

    NFD_LOG_DEBUG("[] Accept failed: " << error.message());
    if (onAcceptFailed)
      onAcceptFailed(error.message());
    return;
  }

  NFD_LOG_DEBUG("[] Incoming connection");

  /*auto linkService = make_unique<face::GenericLinkService>();
  auto transport = make_unique<face::DtnTransport>(std::move(m_socket));
  auto face = make_shared<Face>(std::move(linkService), std::move(transport));
  onFaceCreated(face);*/

  // prepare accepting the next connection
  accept(onFaceCreated, onAcceptFailed);
}

} // namespace nfd
