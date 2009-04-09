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
	Q_UNUSED(args)
	setComponentData( KDeliciousPluginFactory::componentData() );

	if( parent )
		m_parent = dynamic_cast<KHTMLPart*>(parent);

	KActionMenu *menu = new KActionMenu( KIcon("bookmarks-organize.png"), i18n("del.icio.us Plugin"),
		actionCollection() );
	actionCollection()->addAction( "kdelicious menu", menu );
	menu->setDelayed( false );

	KAction *kaction;
	kaction = actionCollection()->addAction( "delicioustag" );
	kaction->setIcon( KIcon("bookmarks-organize.png") );
	kaction->setText( i18n("Save Bookmark...") );
	menu->addAction( kaction );
	connect( kaction, SIGNAL(triggered(bool)),
		this, SLOT(tagPage()) );

	m_browser->http()->ignoreSslErrors();
	connect( m_browser->http(), SIGNAL(authenticationRequired(QString,quint16,QAuthenticator*)),
		this, SLOT(authenticationRequired(QString,quint16,QAuthenticator*)) );
	connect( m_browser->http(), SIGNAL(requestFinished(int,bool)),
		this, SLOT(requestFinished(int,bool)) );
	connect( m_browser->http(), SIGNAL(responseHeaderReceived(QHttpResponseHeader)),
		this, SLOT(responseHeaderReceived(QHttpResponseHeader)) );

}

void KDeliciousPlugin::authenticationRequired( QString hostname,
	quint16 port,
	QAuthenticator *authenticator )
{
	Q_UNUSED(port)
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
			dialog.getTags().split( ' ', QString::SkipEmptyParts ),
			dialog.shared(),
			dialog.replace() );
		connect( request, SIGNAL(failed(QtLicious::PostRequest::Error)),
			this, SLOT(postFailed(QtLicious::PostRequest::Error)) );
		connect( request, SIGNAL(finished()),
			request, SLOT(deleteLater()) );
	}
}

void KDeliciousPlugin::requestFinished( int id, bool error )
{
	Q_UNUSED(id)
	if( error )
	{
		KMessageBox::error( 0, i18n( "Request error!" ), i18n( "Request Error" )  );
	}
}

void KDeliciousPlugin::responseHeaderReceived( const QHttpResponseHeader &header )
{
	kDebug() << "Response code: " << header.reasonPhrase();
}

void KDeliciousPlugin::postFailed( QtLicious::PostRequest::Error error )
{
	Q_UNUSED(error)
	KMessageBox::error( 0, i18n( "Post failed." ), i18n( "Post failed." ) );
}
