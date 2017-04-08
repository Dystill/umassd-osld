#ifndef COPYDIALOG_H
#define COPYDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QClipboard>
#include <QFontDatabase>

namespace Ui {
class CopyDialog;
}

class CopyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CopyDialog(QWidget *parent = 0);
    explicit CopyDialog(QString filePath, QWidget *parent = 0);
    ~CopyDialog();

private slots:
    void on_copyButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::CopyDialog *ui;

    int fontSize = 8;
    int tabSize = 2;
};

#endif // COPYDIALOG_H
