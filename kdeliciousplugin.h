#ifndef KDELICIOUSPLUGIN_H
#define KDELICIOUSPLUGIN_H

#include "browser.h"

#include <kparts/plugin.h>

class KActionMenu;
class KConfig;
class KHTMLPart;

namespace KWallet
{
	class Wallet;
}

class KDeliciousPlugin
	: public KParts::Plugin
{
	Q_OBJECT

	public:
		KDeliciousPlugin(QObject* parent = 0, const QVariantList &args = QVariantList());

	private Q_SLOTS:
		void authenticationRequired( QString hostname,
			quint16 port,
			QAuthenticator *authenticator );
		void tagPage();
		void requestFinished( int id, bool error );
		void responseHeaderReceived( const QHttpResponseHeader &header );
		void postFailed( QtLicious::PostRequest::Error error );

	private:
		KHTMLPart *m_parent;
		KWallet::Wallet *m_wallet;
		KConfig *m_config;
		QtLicious::Browser *m_browser;

};

#endif // KDELICIOUSPLUGIN_H
