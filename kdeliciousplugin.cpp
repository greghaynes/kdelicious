#include "kdeliciousplugin.h"
#include "createbookmarkdialog.h"

#include <kgenericfactory.h>
#include <kparts/part.h>
#include <KLocalizedString>
#include <KActionCollection>
#include <KActionMenu>
#include <KAction>
#include <KPasswordDialog>
#include <KWallet/Wallet>
#include <KConfig>
#include <KAboutData>

static const KAboutData aboutData("kdelicious", 0, ki18n("del.icio.us plugin"), "1.0");
K_PLUGIN_FACTORY( KDeliciousPluginFactory, registerPlugin< KDeliciousPlugin >(); )
K_EXPORT_PLUGIN( KDeliciousPluginFactory( aboutData ) )

KDeliciousPlugin::KDeliciousPlugin(QObject *parent, const QVariantList &args)
	: KParts::Plugin(parent)
{
	setComponentData( KDeliciousPluginFactory::componentData() );

	if( parent )
		m_parent = dynamic_cast<KParts::ReadOnlyPart*>(parent);

	m_wallet = KWallet::Wallet::openWallet( KWallet::Wallet::LocalWallet(), 0 );
	if( !m_wallet->setFolder( "kdelicious" ) )
	{
		m_wallet->createFolder( "kdelicious" );
		m_wallet->setFolder( "kdelicious" );
	}

	KActionMenu *menu = new KActionMenu( KIcon("configure"), i18n("del.icio.us Settings"),
		actionCollection() );
	actionCollection()->addAction( "kdelicious menu", menu );
	menu->setDelayed( false );

	KAction *kaction;
	kaction = actionCollection()->addAction( "delicioustag" );
	kaction->setText( i18n("&Tag this site...") );
	menu->addAction( kaction );
	connect( kaction, SIGNAL(triggered(bool)),
		this, SLOT(tagPage()) );

}

void KDeliciousPlugin::setAccount()
{
	KPasswordDialog dialog( 0,
		KPasswordDialog::ShowUsernameLine );
	dialog.exec();
}

void KDeliciousPlugin::tagPage()
{
	CreateBookmarkDialog dialog( 0 );
	dialog.exec();
}

