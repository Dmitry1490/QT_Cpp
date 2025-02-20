#include "mainwindow.h"
#include <QxOrm_Impl.h>
#include "../include/precompiled.h"

#include <QApplication>
#include "blog.h"
#include "author.h"
#include "comment.h"
#include <QtCore>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Parameters to connect to database
    qx::QxSqlDatabase::getSingleton()->setDriverName("QPSQL");
    qx::QxSqlDatabase::getSingleton()->setDatabaseName("postgres");
    qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
    qx::QxSqlDatabase::getSingleton()->setUserName("postgres");
    qx::QxSqlDatabase::getSingleton()->setPassword("Vipe4ka1");
    qx::QxSqlDatabase::getSingleton()->setPort(5433);
    qx::QxSqlDatabase::getSingleton()->setFormatSqlQueryBeforeLogging(true);
    qx::QxSqlDatabase::getSingleton()->setDisplayTimerDetails(true);

    // Only for debug purpose : assert if invalid offset detected fetching a relation
    qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true);

    // Only for debug purpose : assert if invalid offset detected fetching a relation
    qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true);


    // Create a list of 3 author
    author_ptr author_1; author_1.reset(new author()); author_1->m_name = "author_1"; author_1->m_sex = author::male; author_1->m_birthdate = QDate::currentDate();
    author_ptr author_2; author_2.reset(new author()); author_2->m_name = "author_2"; author_2->m_sex = author::female; author_2->m_birthdate = QDate::currentDate();
    author_ptr author_3; author_3.reset(new author()); author_3->m_name = "author_3"; author_3->m_sex = author::female; author_3->m_birthdate = QDate::currentDate();

    list_author authorX;
    authorX.push_back(author_1);
    authorX.push_back(author_2);
    authorX.push_back(author_3);

    // Insert list of 3 author into database
    QSqlError daoError = qx::dao::insert(authorX);
    qAssert(qx::dao::count<author>() == 3);

    MainWindow w;
    w.show();
    return a.exec();
}
