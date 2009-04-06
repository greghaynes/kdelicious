#include "createbookmarkdialog.h"

#include "ui_newbookmarkwidget.h"

CreateBookmarkDialog::CreateBookmarkDialog( QWidget *parent )
	: KDialog( parent )
	, ui( new Ui::NewBookmarkWidget() )
{
	QWidget *mainWidget = new QWidget( this );
	ui->setupUi( mainWidget );
	setMainWidget( mainWidget );
}

