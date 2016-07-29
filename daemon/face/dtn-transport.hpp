/*
 * dtn-transport.hpp
 *
 *  Created on: Jul 21, 2016
 *      Author: root
 */

#ifndef NDN_DAEMON_FACE_DTN_TRANSPORT_HPP_
#define NDN_DAEMON_FACE_DTN_TRANSPORT_HPP_

#include "transport.hpp"
#include "core/global-io.hpp"
#include <ibrdtn/api/Client.h>

namespace nfd {
namespace face {

class DtnTransport : public Transport
{
public:
  DtnTransport(std::string localEndpoint, std::string remoteEndpoint, std::string ibrdtndHost, uint16_t ibrdtndPort);

  void
  receiveBundle(const dtn::data::Bundle &b);

protected:
  virtual void
  beforeChangePersistency(ndn::nfd::FacePersistency newPersistency) DECL_FINAL;

  virtual void
  doClose() DECL_OVERRIDE;

private:
  virtual void
  doSend(Transport::Packet&& packet) DECL_OVERRIDE;

  std::string m_ibrdtndHost;
  uint16_t m_ibrdtndPort;
};

} // namespace face
} // namespace nfd


#endif /* NDN_DAEMON_FACE_DTN_TRANSPORT_HPP_ */
