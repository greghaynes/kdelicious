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
	buffer->open(QBuffer::ReadWrite);
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
	qhttp->get( path().encodedPath(), buffer );
}

const QVariant &Request::responseData() const
{
	return data;
}

void Request::slotReadyRead()
{
	QXmlInputSource source;
	source.setData( buffer->data() );
	QXmlSimpleReader reader;
	reader.setContentHandler( this );
	reader.setErrorHandler( this );
	if( !reader.parse( source ) )
		qDebug() << "Parsing failed.";
	emit( finished() );
}

bool Request::error( const QXmlParseException &exception )
{
	emit( parsingError( exception.message() ) );
	qDebug() << "Parsing error: " << exception.message();
	return true;
}

bool Request::warning( const QXmlParseException &exception )
{
	qDebug() << "Parsing warning: " << exception.message();
	return true;
}


bool Request::fatalError( const QXmlParseException &exception )
{
	emit( parsingError( exception.message() ) );
	qDebug() << "Fatal parsing error: " << exception.message();
	return true;
}

}

