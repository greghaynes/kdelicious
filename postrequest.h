#ifndef QTLICIOUS_POSTREQUEST_H
#define QTLICIOUS_POSTREQUEST_H

#include "request.h"

namespace QtLicious
{

class PostRequest
	: public Request
{

	public:
		PostRequest( const QUrl &path,
			const QString &name,
			const QString &url,
			const QString &description,
			QList<QString> tags,
			QObject *parent = 0 );

};

}

#endif
