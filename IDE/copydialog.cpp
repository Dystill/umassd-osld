#include "copydialog.h"
#include "ui_copydialog.h"

CopyDialog::CopyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CopyDialog)
{
    ui->setupUi(this);
}

CopyDialog::CopyDialog(QString filePath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CopyDialog)
{
    ui->setupUi(this);

    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setFixedPitch(true);
    font.setPointSize(fontSize);

    ui->textEdit->setFont(font);
    ui->textEdit->setWordWrapMode(QTextOption::NoWrap);
    ui->textEdit->setTabStopWidth(tabSize * ui->textEdit->fontMetrics().width(' '));

    // create the file object
    QFile file(filePath);

    // open the file
    if(file.open(QIODevice::ReadOnly)) {
        // read the file
        QTextStream in(&file);

        // add text to textedit window
        ui->textEdit->setText(in.readAll());
    }
}

CopyDialog::~CopyDialog()
{
    delete ui;
}

void CopyDialog::on_copyButton_clicked()
{
    // set text to the clipboard
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->textEdit->toPlainText());

    // close the window
    this->destroy();
}

void CopyDialog::on_cancelButton_clicked()
{
    this->destroy();
}
