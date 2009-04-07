#include "browser.h"

#include <QTimer>
#include <QDebug>

namespace QtLicious
{

Browser::Browser( QObject *parent )
	: QObject( parent )
	, can_req( true )
	, m_http( new QHttp( delicious_api_host, 0,  this ) )
{
}

Browser::Browser( const QString &apiUrl,
	QObject *parent )
	: QObject( parent )
	, can_req( true )
	, m_http( new QHttp( apiUrl, 0, this ) )
{
	delete m_http;
}

QHttp *Browser::http() const
{
	return m_http;
}

BookmarkRequest *Browser::recentBookmarks()
{
	BookmarkRequest *req = new BookmarkRequest(
		"v1/posts/recent",
		this );
	enqueueRequest( req );
	return req;
}

void Browser::requestFinished()
{
	if( requestQueue.size() > 0 )
		QTimer::singleShot( 1000, this, SLOT(throttleTimeout()) );
}

void Browser::throttleTimeout()
{
	Request *req = requestQueue.dequeue();
	if( !req )
	{
		qDebug() << "Timeout set with empty queue.  Shouldn't happen.";
		return;
	}
	runRequest( req );
}

void Browser::enqueueRequest( Request *req )
{
	if( can_req )
		runRequest( req );
	else
		requestQueue.enqueue( req );
}

void Browser::runRequest( Request *req )
{
	can_req = false;
	connect( req, SIGNAL(finished()),
		this, SLOT(requestFinished()) );
	req->run( http() );
}

}

