/********************************************************************************
** Form generated from reading UI file 'rcasmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RCASMAINWINDOW_H
#define UI_RCASMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RCASMainWindow
{
public:
    QAction *actionNew_session;
    QAction *actionOpen_session;
    QAction *actionQuit;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *home_page;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QWidget *import_page;
    QWidget *session_page;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *listWidget;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *assessment_page;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RCASMainWindow)
    {
        if (RCASMainWindow->objectName().isEmpty())
            RCASMainWindow->setObjectName(QStringLiteral("RCASMainWindow"));
        RCASMainWindow->resize(640, 480);
        actionNew_session = new QAction(RCASMainWindow);
        actionNew_session->setObjectName(QStringLiteral("actionNew_session"));
        actionOpen_session = new QAction(RCASMainWindow);
        actionOpen_session->setObjectName(QStringLiteral("actionOpen_session"));
        actionQuit = new QAction(RCASMainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(RCASMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 641, 421));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(horizontalLayoutWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        home_page = new QWidget();
        home_page->setObjectName(QStringLiteral("home_page"));
        horizontalLayoutWidget_2 = new QWidget(home_page);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(-1, -1, 641, 421));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(horizontalLayoutWidget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMaximumSize(QSize(200, 100));
        pushButton_2->setAutoFillBackground(false);
        pushButton_2->setFlat(false);

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton = new QPushButton(horizontalLayoutWidget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMaximumSize(QSize(200, 100));

        horizontalLayout_2->addWidget(pushButton);

        stackedWidget->addWidget(home_page);
        import_page = new QWidget();
        import_page->setObjectName(QStringLiteral("import_page"));
        stackedWidget->addWidget(import_page);
        session_page = new QWidget();
        session_page->setObjectName(QStringLiteral("session_page"));
        horizontalLayoutWidget_3 = new QWidget(session_page);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(-1, -1, 641, 421));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(horizontalLayoutWidget_3);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);
        listWidget->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_3->addWidget(listWidget);

        groupBox = new QGroupBox(horizontalLayoutWidget_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        verticalLayoutWidget = new QWidget(groupBox);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(-1, 19, 313, 401));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(verticalLayoutWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(groupBox_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_5->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_5->addWidget(pushButton_4);


        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout_3->addWidget(groupBox);

        stackedWidget->addWidget(session_page);
        assessment_page = new QWidget();
        assessment_page->setObjectName(QStringLiteral("assessment_page"));
        stackedWidget->addWidget(assessment_page);

        horizontalLayout->addWidget(stackedWidget);

        RCASMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RCASMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        RCASMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RCASMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RCASMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RCASMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RCASMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew_session);
        menuFile->addAction(actionOpen_session);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(RCASMainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(RCASMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RCASMainWindow)
    {
        RCASMainWindow->setWindowTitle(QApplication::translate("RCASMainWindow", "RCASMainWindow", Q_NULLPTR));
        actionNew_session->setText(QApplication::translate("RCASMainWindow", "New session", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionNew_session->setShortcut(QApplication::translate("RCASMainWindow", "Ctrl+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionOpen_session->setText(QApplication::translate("RCASMainWindow", "Open session", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOpen_session->setShortcut(QApplication::translate("RCASMainWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionQuit->setText(QApplication::translate("RCASMainWindow", "Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("RCASMainWindow", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        pushButton_2->setText(QApplication::translate("RCASMainWindow", "Start new session", Q_NULLPTR));
        pushButton->setText(QApplication::translate("RCASMainWindow", "Load older session", Q_NULLPTR));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QApplication::translate("RCASMainWindow", "Candidate details", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("RCASMainWindow", "Review assessment", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("RCASMainWindow", "Start assessment", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("RCASMainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RCASMainWindow: public Ui_RCASMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RCASMAINWINDOW_H
