#ifndef QTLICIOUS_BOOKMARK_H
#define QTLICIOUS_BOOKMARK_H

#include <QString>
#include <QUrl>
#include <QList>
#include <QDateTime>

namespace QtLicious
{

/**
 * @brief Stores bookmark information
 */
class Bookmark
{

	public:
		Bookmark();
		~Bookmark();

		const QUrl &url() const;
		const QString &description() const;
		const QDateTime &date() const;
		const QString &hash() const;
		const QList<QString> &tags() const;
		void setUrl( const QUrl &url );
		void setDescription( const QString &desc );
		void setDate( const QDateTime &date );
		void setHash( const QString &hash );
		void setTags( const QList<QString> &tags );

	private:
		QUrl m_link;
		QString m_description;
		QDateTime m_time;
		QString m_hash;
		QList<QString> m_tags;

};

}

#endif

