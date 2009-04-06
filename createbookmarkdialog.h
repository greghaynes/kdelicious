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

	private:
		Ui::NewBookmarkWidget *ui;

};

#endif 

