#include "wstart.h"
#include "ui_wstart.h"

wStart::wStart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::wStart)
{
    ui->setupUi(this);
    ui->statusbar->addPermanentWidget(ui->pgbProgress);
    ui->pgbProgress->setVisible(false);
}

wStart::~wStart()
{
    delete ui;
}

void wStart::on_btnStart_clicked()
{
    if (ui->ledInput->text().size() > ui->sbxGlobalI->value())
        QMessageBox::warning(this, "i value smaller than input", "letter count per i is smaller than the input string size.");
    else
    {
        globalI = 0;
        stringSize = 0;
        ui->pgbProgress->setVisible(true);
        ui->centralwidget->setEnabled(false);
        ui->statusbar->showMessage("Monkey is typing...");

        elTimer.restart();
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &wStart::reloadUI);
        timer->start(1000);

        QFuture<void> future;
        QFutureWatcher<void> *futureWatcher = new QFutureWatcher<void>();
        QEventLoop *loop = new QEventLoop();

        future = QtConcurrent::run([=]() { searchString(ui->ledInput->text().toLower(), ui->sbxGlobalI->value()); });
        QObject::connect(futureWatcher, &QFutureWatcher<void>::finished, loop, &QEventLoop::quit);
        futureWatcher->setFuture(future);

        loop->exec();

        timer->stop();
    }

    reloadUI();
    ui->pgbProgress->setVisible(false);
    ui->centralwidget->setEnabled(true);
    ui->pteLastTempString->setPlainText(*tempString);

    ui->statusbar->showMessage("Monkey has finished typing!");
}

void wStart::searchString(QString searchString, int iSize)
{
    int letterListCount = letters.count();

    while (true)
    {
        tempString = new QString();
        for (int i = 0; i < iSize; i++) tempString->append(letters[QRandomGenerator::global()->bounded(letterListCount)]);

        stringSize += tempString->size(); globalI++;

        if (tempString->contains(searchString)) break;

        delete tempString;
    }
}

void wStart::reloadUI()
{
    ui->ledTime->setText(QString::number(elTimer.elapsed() / 1000) + " seconds");
    ui->ledStringLength->setText(QString::number(stringSize) + " letters");
    ui->ledLoops->setText(QString::number(globalI));

    if ((stringSize * 0.000004) > 1000)
        ui->ledByteSize->setText("~ " + QString::number(stringSize * 0.000004 / 1000, 'f', 3) + " GB");
    else
        ui->ledByteSize->setText("~ " + QString::number(stringSize * 0.000004, 'f', 3) + " MB");
}
