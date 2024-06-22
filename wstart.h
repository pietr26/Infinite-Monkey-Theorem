#ifndef WSTART_H
#define WSTART_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QtConcurrent>
#include <QFutureWatcher>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class wStart; }
QT_END_NAMESPACE

class wStart : public QMainWindow
{
    Q_OBJECT

public:
    wStart(QWidget *parent = nullptr);
    ~wStart();

private slots:
    void on_btnStart_clicked();

private:
    Ui::wStart *ui;

    void searchString(QString string, int iSize);

    void reloadUI();

    QString *tempString;
    QElapsedTimer elTimer;
    QTimer *timer;
    qint64 globalI;
    qint64 stringSize;
    const QStringList letters = { "a", "ä", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "ö", "p", "q", "r", "s", "ß", "t", "u", "ü", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " " };
};
#endif // WSTART_H
