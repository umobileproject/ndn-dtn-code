/*
 * dtn-transport.cpp
 *
 *  Created on: Jul 21, 2016
 *      Author: root
 */

#include "dtn-transport.hpp"
#include <ibrdtn/data/EID.h>
#include <ibrdtn/api/Client.h>
#include <ibrcommon/net/socket.h>
#include <ibrcommon/net/socketstream.h>

namespace nfd {
namespace face {

NFD_LOG_INIT("DtnTransport");

DtnTransport::DtnTransport(std::string localEndpoint, std::string remoteEndpoint, std::string ibrdtndHost, uint16_t ibrdtndPort):
		  m_ibrdtndHost(ibrdtndHost), m_ibrdtndPort(ibrdtndPort)
{

  this->setLocalUri(FaceUri(localEndpoint));
  this->setRemoteUri(FaceUri(remoteEndpoint));
  this->setScope(ndn::nfd::FACE_SCOPE_NON_LOCAL);
  this->setPersistency(ndn::nfd::FACE_PERSISTENCY_PERSISTENT);
  this->setLinkType(ndn::nfd::LINK_TYPE_POINT_TO_POINT);
  this->setMtu(MTU_UNLIMITED);
}

void
DtnTransport::receiveBundle(const dtn::data::Bundle &b)
{
  NFD_LOG_FACE_TRACE("Received: " << b.getPayloadLength() << " payload bytes");

  bool isOk = false;

  ibrcommon::BLOB::Reference ref = b.find<dtn::data::PayloadBlock>().getBLOB();

  Block element(ref.iostream()->rdbuf(), ref.iostream()->rdbuf()->in_avail());

  if (!isOk) {
	NFD_LOG_FACE_WARN("Failed to parse incoming packet");
	// This packet won't extend the face lifetime
	return;
  }

  Transport::Packet tp(std::move(element));
  tp.remoteEndpoint = 0;
  this->receive(std::move(tp));
}


void
DtnTransport::beforeChangePersistency(ndn::nfd::FacePersistency newPersistency)
{

}

void
DtnTransport::doClose()
{

}

void
DtnTransport::doSend(Transport::Packet&& packet)
{
  ibrcommon::vaddress ibrdtndAddress(m_ibrdtndHost, m_ibrdtndPort);
  ibrcommon::socketstream ibrdtnSocketStream(new ibrcommon::tcpsocket(ibrdtndAddress));

  // Initiate a client for sending
  dtn::api::Client client(getLocalUri().getHost(), ibrdtnSocketStream, dtn::api::Client::MODE_SENDONLY);

  // create an empty BLOB
  ibrcommon::BLOB::Reference ref = ibrcommon::BLOB::create();

  // copy cin to a BLOB
  (*ref.iostream()) << packet.packet.getBuffer();

  dtn::data::Bundle b;

  // set the destination
  b.destination = dtn::data::EID(getRemoteUri().getHost() + "/" + getRemoteUri().getPort());

  // add payload block with the reference
  b.push_back(ref);

  client << b;

  client.flush();
  client.close();
}

} // namespace face
} // namespace nfd

