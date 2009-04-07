#include "postrequest.h"

namespace QtLicious
{

PostRequest::PostRequest( const QString &path,
	const QString &name,
	const QString &url,
	const QString &description,
	QList<QString> tags,
	QObject *parent )
	: Request( path, parent )
{
	QString fullpath;
	fullpath.append( path );
	fullpath.append( "&url=" );
	fullpath.append( url );
	fullpath.append( "&description=" );
	fullpath.append( name );
	QString tag;
	if( tags.size() > 0 )
	{
		foreach( tag, tags )
			fullpath += tag + " ";
	}
	setPath( fullpath );
}

}
