#include "request.h"

#include <QXmlSimpleReader>
#include <QXmlInputSource>

#include "request.moc"

namespace QtLicious
{

Request::Request( const QString &path, QObject *parent )
	: QObject( parent )
	, m_path( path )
	, m_isFinished( false )
	, buffer( new QBuffer( this ) )
{
	connect( buffer, SIGNAL(readyRead()),
		this, SLOT(slotReadyRead()) );
}

Request::~Request()
{
	delete buffer;
}

const QString &Request::path() const
{
	return m_path;
}

void Request::setPath( const QString &path ) 
{
	m_path = path;
}

bool Request::isFinished() const
{
	return m_isFinished;
}

void Request::run( QHttp *qhttp )
{
	qhttp->get( path(), buffer );
}

const QVariant &Request::responseData() const
{
	return data;
}

void Request::slotReadyRead()
{
	QXmlInputSource source( buffer );
	QXmlSimpleReader reader;
	reader.setContentHandler( this );
	reader.parse( source );
	emit( finished() );
}

}

