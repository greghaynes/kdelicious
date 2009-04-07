#include "bookmarkrequest.h"

#include <QDebug>

namespace QtLicious
{

BookmarkRequest::BookmarkRequest( const QString &path,
	QObject *parent )
	: Request( path, parent )
{
}

bool BookmarkRequest::startDocument()
{
	qDebug() << "Reqest parsing begun.";
	return true;
}

}

