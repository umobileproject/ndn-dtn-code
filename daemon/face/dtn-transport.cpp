/*
 * dtn-transport.cpp
 *
 *  Created on: Jul 21, 2016
 *      Author: root
 */

#include "dtn-transport.hpp"
// #include <ibrdtn/data/EID.h>
#include <ibrcommon/data/BLOB.h>
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

  NFD_LOG_FACE_INFO("Creating DTN transport");
}

void
DtnTransport::receiveBundle(dtn::data::Bundle b)
{
	  NFD_LOG_FACE_INFO("Received: " << b.getPayloadLength() << " payload bytes");

	  bool isOk = false;

	  ibrcommon::BLOB::Reference ref = b.find<dtn::data::PayloadBlock>().getBLOB();

	  std::stringstream stringStream;
	  stringStream << ref.iostream()->rdbuf();
	  std::string stringBuffer = stringStream.str();

	  Block element;

	  // 1. Non-working solution, based on ndn data types.
	  /*
		auto ndnBuffer = std::make_shared<ndn::Buffer>(stringbuffer.begin(), stringbuffer.end());
		ndn::ConstBufferPtr constBuffer = ndnBuffer;
	   */

	  // 2. Working solution, based on getting the buffer directly from the string.
	  /*
		const uint8_t* plainBuffer = reinterpret_cast<const uint8_t*>(&stringBuffer[0]);
		std::tie(isOk, element) = Block::fromBuffer(plainBuffer, stringBuffer.length());
	  */
	  // 3. Test solution
	  uint8_t* plainBuffer = new uint8_t[stringBuffer.length() + 1];
	  std::copy(stringBuffer.begin(), stringBuffer.end(), plainBuffer);
	  std::tie(isOk, element) = Block::fromBuffer(plainBuffer, stringBuffer.length());

	  // NFD_LOG_FACE_INFO("Bundle payload:" << ref.iostream()->rdbuf() << std::flush);
	  // NFD_LOG_FACE_INFO("Bundle payload:" << stringBuffer);

	  if (!isOk) {
		NFD_LOG_FACE_WARN("Failed to parse incoming packet");
		// This packet won't extend the face lifetime
		return;
	  }

	  Transport::Packet tp(std::move(element));
	  tp.remoteEndpoint = 0;
	  this->receive(std::move(tp));
	  // this->receive(tp);
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
  try {

	  ibrcommon::vaddress ibrdtndAddress(m_ibrdtndHost, m_ibrdtndPort);
	  ibrcommon::socketstream ibrdtnSocketStream(new ibrcommon::tcpsocket(ibrdtndAddress));

	  std::string localURI = getLocalUri().toString();
	  std::string localHost = getLocalUri().getHost();
	  std::string ibrdtnHost = m_ibrdtndHost;

	  // Initiate a client for sending
	  dtn::api::Client client(getLocalUri().getPath().substr(1), ibrdtnSocketStream, dtn::api::Client::MODE_SENDONLY);
	  client.connect();

	  // create an empty BLOB
	  ibrcommon::BLOB::Reference ref = ibrcommon::BLOB::create();

	  std::string str(packet.packet.begin(),packet.packet.end());
	  // cout << str;
	  // std::string test << packet.packet.getBuffer();
	  // copy cin to a BLOB
	  // (*ref.iostream()) << packet.packet.getBuffer();
	  (*ref.iostream()) << str;
	  dtn::data::Bundle b;

	  std::string host = getRemoteUri().getHost();
	  std::string port = getRemoteUri().getPath();
	  std::string destinationAddress = getRemoteUri().getScheme() + "://" + getRemoteUri().getHost() + getRemoteUri().getPath();
	  // set the destination
	  // dtn::data::EID eid("dtn://ubuntu2/nfd");

	  b.destination = destinationAddress;

	  // add payload block with the reference
	  b.push_back(ref);

	  client << b;

	  client.flush();
	  client.close();

	  ibrdtnSocketStream.close();
  }catch (const ibrcommon::IOException &ex)
  {
	  NFD_LOG_INFO("IBR-DTN Error: " << ex.what());
	  // connection already closed, the daemon was faster
  }
}


} // namespace face
} // namespace nfd

