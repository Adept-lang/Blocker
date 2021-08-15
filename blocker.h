#ifndef BLOCKER_H
#define BLOCKER_H

#include <QMainWindow>
#include <windows.h>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class Blocker; }
QT_END_NAMESPACE


class Reseacrher : public QObject{
    Q_OBJECT

public:
    explicit Reseacrher(QObject* parent = nullptr);

public slots:
private:

    bool IsProcessRun(wchar_t*);

public slots:
   // void on_pushButton_3_clicked();
    void run(QVector<QString> programs,bool);
signals:
};


class Blocker : public QMainWindow
{
    Q_OBJECT

public:
    Blocker(QWidget *parent = nullptr);
    ~Blocker();
    static QString allFiles;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void keyPressEvent(QKeyEvent *event);



    void on_checkBox_stateChanged();

signals:
    void finished();
    void start(QVector<QString>, bool);


private:
    Ui::Blocker *ui;
    QString currentFile;
    Reseacrher* res;
    void about();
    DWORD GetProcessByExeName(wchar_t *ExeName);
    bool IsProcessRun(wchar_t *ExeName);
    QThread* thread_1;       // Первый поток
    QThread* thread_2;

};
#endif // BLOCKER_H
