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
#include <KMessageBox>
#include <DOM/HTMLDocument>

#include <QAuthenticator>
#include <QHttpResponseHeader>

static const KAboutData aboutData("kdelicious", 0, ki18n("del.icio.us plugin"), "1.0");
K_PLUGIN_FACTORY( KDeliciousPluginFactory, registerPlugin< KDeliciousPlugin >(); )
K_EXPORT_PLUGIN( KDeliciousPluginFactory( aboutData ) )

KDeliciousPlugin::KDeliciousPlugin(QObject *parent, const QVariantList &args)
	: KParts::Plugin(parent)
	, m_browser( new QtLicious::Browser( this ) )
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

	kaction = actionCollection()->addAction( "deliciousaccount" );
	kaction->setText( i18n( "&Account" ) );
	menu->addAction( kaction );
	connect( kaction, SIGNAL(triggered(bool)),
		this, SLOT(setAccount()) );

	m_browser->http()->ignoreSslErrors();
	connect( m_browser->http(), SIGNAL(authenticationRequired(QString,quint16,QAuthenticator*)),
		this, SLOT(authenticationRequired(QString,quint16,QAuthenticator*)) );
	connect( m_browser->http(), SIGNAL(requestFinished(int,bool)),
		this, SLOT(requestFinished(int,bool)) );
	connect( m_browser->http(), SIGNAL(responseHeaderReceived(QHttpResponseHeader)),
		this, SLOT(responseHeaderReceived(QHttpResponseHeader)) );

}

void KDeliciousPlugin::setAccount( const QString &prompt )
{
	KPasswordDialog dialog( 0,
		KPasswordDialog::ShowUsernameLine );
	dialog.setPrompt( prompt );
	if( dialog.exec() )
	{
		m_browser->http()->setUser( dialog.username(), dialog.password() );
	}
}

void KDeliciousPlugin::setAccount()
{
	setAccount( i18n("Enter your del.icio.us account information.") );
}

void KDeliciousPlugin::authenticationRequired( QString hostname,
	quint16 port,
	QAuthenticator *authenticator )
{
	KPasswordDialog dialog( 0,
		KPasswordDialog::ShowUsernameLine );
	dialog.setPrompt( "Authentication required for " + hostname );
	if( dialog.exec() )
	{
		authenticator->setUser( dialog.username() );
		authenticator->setPassword( dialog.password() );
	}
}

void KDeliciousPlugin::tagPage()
{
	CreateBookmarkDialog dialog( 0 );
	QtLicious::PostRequest *request;
	dialog.setTitle( m_parent->htmlDocument().title().string() );
	dialog.setUrl( m_parent->url().url() );
	QList<QString> list;
	if( dialog.exec() )
	{
		request = m_browser->postBookmark( dialog.getTitle(),
			dialog.getUrl(),
			dialog.getDescription(),
			list );
		connect( request, SIGNAL(failed(QtLicious::PostRequest::Error)),
			this, SLOT(postFailed(QtLicious::PostRequest::Error)) );
	}
}

void KDeliciousPlugin::requestFinished( int id, bool error )
{
	if( error )
	{
		KMessageBox::error( 0, i18n( "Request error!" ), i18n( "Request Error" )  );
	}
}

void KDeliciousPlugin::responseHeaderReceived( const QHttpResponseHeader &header )
{
	if( header.statusCode() != 200 )
	{
		kDebug() << "Non 200 response code: " << header.reasonPhrase();
	}
}

void KDeliciousPlugin::postFailed( QtLicious::PostRequest::Error error )
{
	KMessageBox::error( 0, i18n( "Post failed." ), i18n( "Post failed." ) );
}
