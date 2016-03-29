/*
 * PosixLinkManager.h
 *
 *  Created on: 11.10.2012
 *      Author: morgenro
 */

#ifndef POSIXLINKMANAGER_H_
#define POSIXLINKMANAGER_H_

#include "ibrcommon/link/LinkManager.h"
#include "ibrcommon/net/vinterface.h"
#include "ibrcommon/net/vaddress.h"
#include "ibrcommon/link/LinkMonitor.h"
#include <list>

namespace ibrcommon
{
	class PosixLinkManager : public LinkManager
	{
	public:
		PosixLinkManager();
		virtual ~PosixLinkManager();

		void up() throw();
		void down() throw();

		const vinterface getInterface(int index) const;
		const std::list<vaddress> getAddressList(const vinterface &iface, const std::string &scope = "");

		virtual void addEventListener(const vinterface &iface, LinkManager::EventCallback *cb) throw ();
		virtual void removeEventListener(const vinterface&, LinkManager::EventCallback*) throw ();
		virtual void removeEventListener(LinkManager::EventCallback*) throw ();

	private:
		LinkMonitor _lm;
	};
} /* namespace ibrcommon */
#endif /* POSIXLINKMANAGER_H_ */
