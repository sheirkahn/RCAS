#include "rcasmainwindow.h"
#include "ui_rcasmainwindow.h"
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <iostream>

bool RCASMainWindow::validate_new_session() const
{
    if (ui->assessorname_edit->text().isEmpty())
    {
        return false;
    }

    if (!ui->assessmentdate_edit->date().isValid() || ui->assessmentdate_edit->date() < QDate::currentDate())
    {
        return false;
    }

    if (!QFile::exists (ui->candidatelist_edit->text()))
    {
        return false;
    }

    return true;
}

bool RCASMainWindow::readCandidatesFromCSVFile (const QString &fileName) const
{
    QFile file(fileName);
    if (!file.open (QIODevice::ReadOnly))
    {
        return false;
    }

    QByteArray header = file.readLine ();
    if (header.isEmpty())
    {
        return false;
    }

    QList <QByteArray> headerWords = header.split(',');
    int numHeaderWords = headerWords.size();
    if (numHeaderWords != 11)
    {
        return false;
    }

    QList <QByteArray> lines;
    while (!file.atEnd ())
    {
        lines.append(file.readLine ());
    }

    int numCandidates = lines.size();
    if (!numCandidates)
    {
        return false;
    }

    ui->candidate_table->setRowCount(numCandidates);
    ui->candidate_table->setColumnCount(10);

    // Populate the table widget with the list of candidates
    for (int i = 0; i < numCandidates; i++)
    {
        QList <QByteArray> candidateDetails = lines[i].split(',');

        for (int j = 1; j < numHeaderWords; j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem (QString (candidateDetails[j]));
            ui->candidate_table->setItem(i, j-1, item);
        }
    }

    return true;
}
