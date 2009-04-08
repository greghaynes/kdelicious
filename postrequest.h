#ifndef QTLICIOUS_POSTREQUEST_H
#define QTLICIOUS_POSTREQUEST_H

#include "request.h"

namespace QtLicious
{

class PostRequest
	: public Request
{
	Q_OBJECT

	public:
		enum Error
		{
			SomethingWentWrong // This defined by the API
		};

		PostRequest( const QUrl &path,
			const QString &name,
			const QString &url,
			const QString &description,
			QList<QString> tags,
			QObject *parent = 0 );

		bool startElement( const QString &namespaceURI,
			const QString &localName,
			const QString &qName,
			const QXmlAttributes &attr );

	Q_SIGNALS:
		void failed( QtLicious::PostRequest::Error error );

};

}

#endif
