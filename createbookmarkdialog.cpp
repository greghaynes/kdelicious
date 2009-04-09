#include "createbookmarkdialog.h"


#include "ui_newbookmarkwidget.h"

CreateBookmarkDialog::CreateBookmarkDialog( QWidget *parent )
	: KDialog( parent )
	, ui( new Ui::NewBookmarkWidget() )
{
	QWidget *mainWidget = new QWidget( this );
	ui->setupUi( mainWidget );
	setMainWidget( mainWidget );
	setWindowTitle( i18n("Save del.icio.us Bookmark") );
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

QString CreateBookmarkDialog::getDescription() const 
{
	return ui->descriptionTextEdit->toPlainText();
}

QString CreateBookmarkDialog::getUrl() const
{
	return ui->urlLineEdit->text();
}

QString CreateBookmarkDialog::getTags() const
{
	return ui->tagsLineEdit->text();
}

QString CreateBookmarkDialog::getTitle() const
{
	return ui->titleLineEdit->text();
}

bool CreateBookmarkDialog::replace() const
{
	return ui->replaceCheckbox->checkState() == Qt::Checked;
}

bool CreateBookmarkDialog::shared() const
{
	return ui->privateCheckbox->checkState() == Qt::Unchecked;
}
