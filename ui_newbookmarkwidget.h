#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading ui file 'newbookmarkwidget.ui'
**
** Created: Mon Apr 6 15:38:28 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NEWBOOKMARKWIDGET_H
#define UI_NEWBOOKMARKWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewBookmarkWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *linkLineEdit;
    QLabel *label_2;
    QLineEdit *tagsLineEdit;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *NewBookmarkWidget)
    {
        if (NewBookmarkWidget->objectName().isEmpty())
            NewBookmarkWidget->setObjectName(QString::fromUtf8("NewBookmarkWidget"));
        NewBookmarkWidget->resize(316, 170);
        verticalLayout = new QVBoxLayout(NewBookmarkWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(NewBookmarkWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        linkLineEdit = new QLineEdit(NewBookmarkWidget);
        linkLineEdit->setObjectName(QString::fromUtf8("linkLineEdit"));

        gridLayout->addWidget(linkLineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(NewBookmarkWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        tagsLineEdit = new QLineEdit(NewBookmarkWidget);
        tagsLineEdit->setObjectName(QString::fromUtf8("tagsLineEdit"));

        gridLayout->addWidget(tagsLineEdit, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 93, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(NewBookmarkWidget);

        QMetaObject::connectSlotsByName(NewBookmarkWidget);
    } // setupUi

    void retranslateUi(QWidget *NewBookmarkWidget)
    {
        NewBookmarkWidget->setWindowTitle(tr2i18n("Form", 0));
        label->setText(tr2i18n("Link:", 0));
        label_2->setText(tr2i18n("Tags:", 0));
        Q_UNUSED(NewBookmarkWidget);
    } // retranslateUi

};

namespace Ui {
    class NewBookmarkWidget: public Ui_NewBookmarkWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // NEWBOOKMARKWIDGET_H

