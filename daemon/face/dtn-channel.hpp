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
#include <ibrdtn/data/EID.h>
#include <ibrdtn/api/Client.h>
#include <ibrcommon/net/socket.h>
#include <ibrcommon/net/socketstream.h>

namespace nfd {

class AsyncIbrDtnClient;

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
  DtnChannel(const std::string &endpointPrefix, const std::string &endpointAffix, const std::string &ibrdtnHost, uint16_t ibrdtndPort);

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
         const FaceCreationFailedCallback& onReceiveFailed);
         //int backlog);

  bool
  isListening() const;
  void
  processBundle(const dtn::data::Bundle &b, const FaceCreatedCallback& onFaceCreated, const FaceCreationFailedCallback& onReceiveFailed);

  void
  connect(const std::string &remoteEndpoint,
          ndn::nfd::FacePersistency persistency,
          const FaceCreatedCallback& onFaceCreated,
          const FaceCreationFailedCallback& onConnectFailed);

  std::pair<bool, shared_ptr<Face>>
  createFace(const std::string &remoteEndpoint, ndn::nfd::FacePersistency persistency);

  private:
  void
  accept(const FaceCreatedCallback& onFaceCreated,
         const FaceCreationFailedCallback& onAcceptFailed);

  void
  handleAccept(const boost::system::error_code& error,
               const FaceCreatedCallback& onFaceCreated,
               const FaceCreationFailedCallback& onAcceptFailed);

private:
  std::string m_endpointPrefix;
  std::string m_endpointAffix;
  std::string m_ibrdtnHost;
  uint16_t m_ibrdtndPort;

  std::string m_remoteEndpoint;

  bool m_is_open;
  // std::map<ibrdtn::Endpoint, shared_ptr<Face>> m_channelFaces;
  std::map<std::string, shared_ptr<Face>> m_channelFaces;

  AsyncIbrDtnClient *m_pIbrDtnClient;

  //boost::asio::ip::tcp::acceptor m_acceptor;
  //boost::asio::ip::tcp::socket m_acceptSocket;
};

inline bool
DtnChannel::isListening() const
{
  return m_is_open;
  //return m_acceptor.is_open();
}

	// typedef std::function< void(dtn::data::Bundle &b) > BundleReceivedCallback;
class AsyncIbrDtnClient : public dtn::api::Client
{
public:
	AsyncIbrDtnClient(const std::string &app, const std::string &host, uint16_t port, DtnChannel *pChannel,
			const FaceCreatedCallback& onFaceCreated, const FaceCreationFailedCallback& onReceiveFailed);

	virtual ~AsyncIbrDtnClient();

protected:
	/**
	 * In this API bundles are received asynchronous. To receive bundles it is necessary
	 * to overload the Client::received()-method. This will be call on a incoming bundles
	 * by another thread.
	 */
	// void received(const dtn::data::Bundle &b);
	virtual void received(const dtn::data::Bundle &b);

	ibrcommon::vaddress m_ibrdtndAddress;
	ibrcommon::socketstream m_socketStream;

	DtnChannel *m_pChannel;
	FaceCreatedCallback OnFaceCreated;
	FaceCreationFailedCallback OnReceiveFailed;
};
} // namespace nfd

#endif // NFD_DAEMON_FACE_DTN_CHANNEL_HPP
