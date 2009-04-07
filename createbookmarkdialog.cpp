#include "createbookmarkdialog.h"

#include "ui_newbookmarkwidget.h"

CreateBookmarkDialog::CreateBookmarkDialog( QWidget *parent )
	: KDialog( parent )
	, ui( new Ui::NewBookmarkWidget() )
{
	QWidget *mainWidget = new QWidget( this );
	ui->setupUi( mainWidget );
	setMainWidget( mainWidget );
	resize( 500, 300 );
}

void CreateBookmarkDialog::setTitle( const QString &title )
{
	ui->titleLineEdit->setText( title );
}

void CreateBookmarkDialog::setUrl( const QString& url )
{
	ui->urlLineEdit->setText( url );
}
