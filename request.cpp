#include "request.h"

#include <QXmlSimpleReader>
#include <QXmlInputSource>

#include <QDebug>

#include "request.moc"

namespace QtLicious
{

Request::Request( const QUrl &path, QObject *parent )
	: QObject( parent )
	, m_path( path )
	, buffer( new QBuffer( this ) )
	, m_isFinished( false )
{
	connect( buffer, SIGNAL(readyRead()),
		this, SLOT(slotReadyRead()) );
}

Request::~Request()
{
	delete buffer;
}

const QUrl &Request::path() const
{
	return m_path;
}

void Request::setPath( const QUrl &path ) 
{
	m_path = path;
}

bool Request::isFinished() const
{
	return m_isFinished;
}

void Request::run( QHttp *qhttp )
{
	qDebug() << "Running" << path().toEncoded();
	qhttp->get( path().toEncoded(), buffer );
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

