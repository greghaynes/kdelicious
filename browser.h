#ifndef QTLICIOUS_H
#define QTLICIOUS_H

#include "request.h"
#include "bookmarkrequest.h"
#include "postrequest.h"

#include <QObject>
#include <QString>
#include <QQueue>
#include <QUrl>

static const char *delicious_api_host = "api.del.icio.us";

namespace QtLicious
{

/**
 * @brief An asyncronous interface for making del.icio.us requests.
 *
 * Methods for requesting del.icio.us data return Request subclasses
 * which are queue'd for processing.  If a request is deleted before
 * processing begins the request will be removed from the queue.
 * Each request can be deleted after it has completed, otherwise it
 * will be deleted upon destruction of the Browser instance which
 * created it.
 */
class Browser
	: public QObject
{
	Q_OBJECT

	public:
		Browser( QObject *parent = 0 );
		Browser( const QString &apiHost = delicious_api_host,
			QObject *parent = 0 );

		QHttp *http() const;
		BookmarkRequest *recentBookmarks();
		PostRequest *postBookmark( const QString &description,
			const QString &url,
			const QString &notes,
			QList<QString> tags,
			bool shared = true,
			bool replace = true );

	private Q_SLOTS:
		void requestFinished();
		void throttleTimeout();

	private:
		void enqueueRequest( Request *req );
		void runRequest( Request *req );

		bool can_req;
		QQueue<Request*> requestQueue;
		QHttp *m_http;

};

}

#endif

