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

#include "dtn-factory.hpp"
namespace nfd {

shared_ptr<DtnChannel>
DtnFactory::createChannel(const std::string &endpointPrefix, const std::string &endpointAffix, const std::string ibrdtndHost, uint16_t ibrdtndPort)
{
  auto channel = findChannel(endpointAffix);
  if (channel)
    return channel;

  channel = make_shared<DtnChannel>(endpointPrefix, endpointAffix, ibrdtndHost, ibrdtndPort);
  m_channels[endpointAffix] = channel;
  return channel;
}

void
DtnFactory::createFace(const FaceUri& uri,
                              ndn::nfd::FacePersistency persistency,
                              const FaceCreatedCallback& onCreated,
                              const FaceCreationFailedCallback& onConnectFailed)
{
  // BOOST_THROW_EXCEPTION(Error("DtnFactory 'createFace' not implemented"));
  std::string dtnEndpoint = uri.getScheme() + "://" + uri.getHost() + uri.getPath();
  std::string dtnAffix = uri.getPath();

  // very simple logic for now
  for (const auto& i : m_channels) {
	if (i.first == dtnAffix ) {
	  i.second->connect(dtnEndpoint, persistency, onCreated, onConnectFailed);
	  return;
	}
  }

  onConnectFailed("No channels available to connect to " + dtnEndpoint);
}

std::vector<shared_ptr<const Channel>>
DtnFactory::getChannels() const
{
  std::vector<shared_ptr<const Channel>> channels;
  channels.reserve(m_channels.size());

  for (const auto& i : m_channels)
    channels.push_back(i.second);

  return channels;
}

shared_ptr<DtnChannel>
DtnFactory::findChannel(const std::string &endpointAffix) const
{
  auto i = m_channels.find(endpointAffix);
  if (i != m_channels.end())
    return i->second;
  else
    return nullptr;
}

} // namespace nfd
