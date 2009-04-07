#include "bookmark.h"

namespace QtLicious
{

Bookmark::Bookmark()
{
}

Bookmark::~Bookmark()
{
}

const QUrl &Bookmark::url() const
{
	return m_link;
}

const QString &Bookmark::description() const
{
	return m_description;
}

const QDateTime &Bookmark::date() const
{
	return m_time;
}

const QString &Bookmark::hash() const
{
	return m_hash;
}

const QList<QString> &Bookmark::tags() const
{
	return m_tags;
}

void Bookmark::setUrl( const QUrl &url )
{
	m_link = url;
}

void Bookmark::setDescription( const QString &desc )
{
	m_description = desc;
}

void Bookmark::setDate( const QDateTime &date )
{
	m_time = date;
}

void Bookmark::setHash( const QString &hash )
{
	m_hash = hash;
}

void Bookmark::setTags( const QList<QString> &tags )
{
	m_tags = tags;
}

}

