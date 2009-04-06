#ifndef KDELICIOUSPLUGIN_H
#define KDELICIOUSPLUGIN_H

#include <kparts/plugin.h>

class KActionMenu;
class KConfig;

namespace KParts
{
	class ReadOnlyPart;
}

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
		void setAccount();
		void tagPage();

	private:
		KParts::ReadOnlyPart *m_parent;
		KWallet::Wallet *m_wallet;
		KConfig *m_config;

};

#endif // KDELICIOUSPLUGIN_H
