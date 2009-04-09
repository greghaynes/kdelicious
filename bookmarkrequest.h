#ifndef QTLICIOUS_BOOKMARKREQUEST_H
#define QTLICIOUS_BOOKMARKREQUEST_H

#include "request.h"


namespace QtLicious
{

class BookmarkRequest
	: public Request
{

	public:
		BookmarkRequest( const QUrl &path,
			QObject *parent = 0 );

		bool startDocument();

};

}

#endif

