#ifndef QTLICIOUS_REQUEST_H
#define QTLICIOUS_REQUEST_H

#include <QObject>
#include <QString>
#include <QBuffer>
#include <QHttp>
#include <QUrl>
#include <QVariant>
#include <QXmlDefaultHandler>

namespace QtLicious
{

class Request
	: public QObject
	, public QXmlDefaultHandler
{
	Q_OBJECT

	public:
		Request( const QUrl &path,
			QObject *parent = 0 );
		virtual ~Request();

		const QUrl &path() const;
		void setPath( const QUrl &path );
		bool isFinished() const;

		/**
		 * @brief Run the request.
		 *
		 * Do not use this function directly, it needs to
		 * be called from Browser to make sure requests are
		 * throttled.
		 */
		void run( QHttp *qhttp );
		const QVariant &responseData() const;

		bool error( const QXmlParseException &exception );
		bool warning( const QXmlParseException &exception );
		bool fatalError( const QXmlParseException &exception );

	Q_SIGNALS:
		void finished();
		void parsingError( QString message );

	protected:
		void emitFinished();

		QVariant data;

	private Q_SLOTS:
		void slotReadyRead();

	private:
		QUrl m_path;
		QBuffer *buffer;
		bool m_isFinished;

};

}

#endif

