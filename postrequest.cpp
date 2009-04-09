#include "postrequest.h"

#include <QDebug>
#include <QXmlAttributes>
#include <QXmlParseException>

namespace QtLicious
{

PostRequest::PostRequest( const QUrl &path,
	const QString &description,
	const QString &url,
	const QString &notes,
	QList<QString> tags,
	bool shared,
	bool replace,
	QObject *parent )
	: Request( path, parent )
{
	QUrl newPath;
	QList<QPair<QString, QString> > arglist;
	arglist.append( QPair<QString, QString>( "url", url ) );
	arglist.append( QPair<QString, QString>( "description", description ) );
	if( !notes.isEmpty() )
		arglist.append( QPair<QString, QString>( "extended", notes ) );
	QString tag, tagarg;
	if( tags.size() > 0 )
	{
		foreach( tag, tags )
			tagarg.append( tag + " " );
	}
	if( !shared )
		arglist.append( QPair<QString, QString>( "shared", "no" ) );
	if( !replace )
		arglist.append( QPair<QString, QString>( "replace", "no" ) );
	arglist.append( QPair<QString, QString>( "tags", tagarg ) );
	newPath.setPath( path.toString() );
	newPath.setQueryItems( arglist );
	setPath( newPath );
}

bool PostRequest::startElement( const QString &namespaceURI,
	const QString &localName,
	const QString &qName,
	const QXmlAttributes &attr )
{
	Q_UNUSED(namespaceURI);
	Q_UNUSED(qName)
	if( localName == "result" && attr.value( "code" ) == "something went wrong" )
	{
		emit( failed( SomethingWentWrong ) );
	}
	return true;
}

}
