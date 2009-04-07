#ifndef QTLICIOUS_BOOKMARKREQUEST_H
#define QTLICIOUS_BOOKMARKREQUEST_H

#include "request.h"

#include <QString>

namespace QtLicious
{

class BookmarkRequest
	: public Request
{

	public:
		BookmarkRequest( const QString &path,
			QObject *parent = 0 );

		bool startDocument();

};

}

#endif

