#include "postrequest.h"

#include <QDebug>
#include <QXmlAttributes>
#include <QXmlParseException>

namespace QtLicious
{

PostRequest::PostRequest( const QUrl &path,
	const QString &name,
	const QString &url,
	const QString &description,
	QList<QString> tags,
	QObject *parent )
	: Request( path, parent )
{
	QUrl newPath;
	QList<QPair<QString, QString> > arglist;
	arglist.append( QPair<QString, QString>( "url", url ) );
	arglist.append( QPair<QString, QString>( "description", name ) );
	arglist.append( QPair<QString, QString>( "extended", description ) );
	QString tag, tagarg;
	if( tags.size() > 0 )
	{
		foreach( tag, tags )
			tagarg.append( tag + " " );
	}
	arglist.append( QPair<QString, QString>( "tag", tagarg ) );
	newPath.setPath( path.toString() );
	newPath.setQueryItems( arglist );
	setPath( newPath );
}

bool PostRequest::startElement( const QString &namespaceURI,
	const QString &localName,
	const QString &qName,
	const QXmlAttributes &attr )
{
	if( localName == "result" && attr.value( "code" ) == "something went wrong" )
	{
		emit( failed( SomethingWentWrong ) );
	}
	return true;
}

}
