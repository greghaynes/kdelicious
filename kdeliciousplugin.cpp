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
#include <KHTMLPart>
#include <DOM/HTMLDocument>

static const KAboutData aboutData("kdelicious", 0, ki18n("del.icio.us plugin"), "1.0");
K_PLUGIN_FACTORY( KDeliciousPluginFactory, registerPlugin< KDeliciousPlugin >(); )
K_EXPORT_PLUGIN( KDeliciousPluginFactory( aboutData ) )

KDeliciousPlugin::KDeliciousPlugin(QObject *parent, const QVariantList &args)
	: KParts::Plugin(parent)
{
	setComponentData( KDeliciousPluginFactory::componentData() );

	if( parent )
		m_parent = dynamic_cast<KHTMLPart*>(parent);

	KActionMenu *menu = new KActionMenu( KIcon("bookmarks-organize.png"), i18n("del.icio.us Settings"),
		actionCollection() );
	actionCollection()->addAction( "kdelicious menu", menu );
	menu->setDelayed( false );

	KAction *kaction;
	kaction = actionCollection()->addAction( "delicioustag" );
	kaction->setIcon( KIcon("bookmarks-organize.png") );
	kaction->setText( i18n("&Tag this site...") );
	menu->addAction( kaction );
	connect( kaction, SIGNAL(triggered(bool)),
		this, SLOT(tagPage()) );

}

void KDeliciousPlugin::setAccount()
{
	KPasswordDialog dialog( 0,
		KPasswordDialog::ShowUsernameLine );
	if( dialog.exec() )
	{
		
	}
}

void KDeliciousPlugin::tagPage()
{
	CreateBookmarkDialog dialog( 0 );
	dialog.setTitle( m_parent->htmlDocument().title().string() );
	dialog.setUrl( m_parent->url().url() );
	dialog.exec();
}

