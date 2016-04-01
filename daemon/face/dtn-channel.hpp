/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014  Regents of the University of California,
 *                     Arizona Board of Regents,
 *                     Colorado State University,
 *                     University Pierre & Marie Curie, Sorbonne University,
 *                     Washington University in St. Louis,
 *                     Beijing Institute of Technology
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
 **/

#ifndef NFD_DAEMON_FACE_DTN_CHANNEL_HPP
#define NFD_DAEMON_FACE_DTN_CHANNEL_HPP

#include "channel.hpp"
#include "core/global-io.hpp"

namespace nfd {

namespace dtn {
//typedef const char* Endpoint;
typedef uint16_t Endpoint;
} // namespace dtn

/**
 * \brief Class implementing a local channel to create faces
 *
 * Channel can create faces as a response to incoming IPC connections
 * (DtnChannel::listen needs to be called for that to work).
 */
class DtnChannel : public Channel
{
public:
  /**
   * \brief DtnChannel-related error
   */
  struct Error : public std::runtime_error
  {
    Error(const std::string& what) : std::runtime_error(what) {}
  };

  /**
   * \brief Create Dtn channel for the specified endpoint
   *
   * To enable creation of faces upon incoming connections, one
   * needs to explicitly call DtnChannel::listen method.
   */
  explicit
  DtnChannel(const dtn::Endpoint& endpoint, uint16_t port);
  //DtnChannel();

  ~DtnChannel() DECL_OVERRIDE;

  /**
   * \brief Enable listening on the local endpoint, accept connections,
   *        and create faces when a connection is made
   * \param onFaceCreated  Callback to notify successful creation of the face
   * \param onAcceptFailed Callback to notify when channel fails (accept call
   *                       returns an error)
   * \param backlog        The maximum length of the queue of pending incoming
   *                       connections
   */
  void
  listen(const FaceCreatedCallback& onFaceCreated,
         const FaceCreationFailedCallback& onAcceptFailed);//,
         //int backlog);

  bool
  isListening() const;

private:
  void
  accept(const FaceCreatedCallback& onFaceCreated,
         const FaceCreationFailedCallback& onAcceptFailed);

  void
  handleAccept(const boost::system::error_code& error,
               const FaceCreatedCallback& onFaceCreated,
               const FaceCreationFailedCallback& onAcceptFailed);

private:
  dtn::Endpoint m_endpoint;
  uint16_t m_port;
  bool m_is_open;
  std::map<dtn::Endpoint, shared_ptr<Face>> m_channelFaces;

  //boost::asio::ip::tcp::acceptor m_acceptor;
  //boost::asio::ip::tcp::socket m_acceptSocket;
};

inline bool
DtnChannel::isListening() const
{
  return m_is_open;
  //return m_acceptor.is_open();
}

} // namespace nfd

#endif // NFD_DAEMON_FACE_DTN_CHANNEL_HPP
