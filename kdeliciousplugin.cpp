#include "kdeliciousplugin.h"

#include <kgenericfactory.h>
#include <kparts/part.h>
#include <KLocalizedString>
#include <KActionCollection>
#include <KActionMenu>
#include <KAction>
#include <KPasswordDialog>
#include <KWallet>
#include <KConfig>

K_PLUGIN_FACTORY( KDeliciousPluginFactory, registerPlugin< KDeliciousPlugin >(); )
K_EXPORT_PLUGIN( KDeliciousPluginFactory( "kdeliciousplugin" ) )

KDeliciousPlugin::KDeliciousPlugin(QObject *parent, const QVariantList &args)
	: Plugin(parent)
{
	if( parent )
		m_parent = dynamic_cast<KParts::ReadOnlyPart*>(parent);

	m_menu = new KActionMenu(i18n("KDelicious"), actionCollection());
	KAction *kaction = actionCollection()->addAction( "action delicioustag", m_menu );
	m_menu->setDelayed( false );

	kaction = actionCollection()->addAction( "delicioustag" );
	kaction->setText( i18n("Tag this site...") );

	kaction = actionCollection()->addAction( "deliciousconfig" );
	kaction->setText( i18n("Settings...") );
}

void KDeliciousPlugin::setAccount()
{
	KPasswordDialog dialog( 0,
		KPasswordDialog::ShowUsernameLine );
	dialog.exec();
}
