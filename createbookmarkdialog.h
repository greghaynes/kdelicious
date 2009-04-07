#ifndef KDELICIOUSPLUGIN_CREATE_BOOKMARK_DIALOG_H
#define KDELICIOUSPLUGIN_CREATE_BOOKMARK_DIALOG_H

#include <KDialog>

namespace Ui
{
	class NewBookmarkWidget;
}

class CreateBookmarkDialog
	: public KDialog
{

	public:
		CreateBookmarkDialog( QWidget *parent = 0 );

		void setTitle( const QString &title );
		void setUrl( const QString &url );
		QString getUrl() const;
		QString getTitle() const;
		QString getDescription() const;
		QString getTags() const;

	private:

		Ui::NewBookmarkWidget *ui;

};

#endif 

