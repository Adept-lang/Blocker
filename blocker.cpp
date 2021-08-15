#include "blocker.h"
#include "ui_blocker.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include  <QSinglePointEvent>
#include <QDebug>
#include "tlhelp32.h"
#include <string.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>
#include "exampleobject.h"



Blocker::Blocker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Blocker)
{
    ui->setupUi(this);
   // ui->menuAbout->
    QAction *actionAbout = new QAction("&About",this);
    menuBar()->addAction(actionAbout);
    connect(actionAbout, &QAction::triggered, this, &Blocker::about);

    res = new Reseacrher();

    connect(this,SIGNAL(start(QVector<QString>,bool)),res,SLOT(run(QVector<QString>,bool)));

    thread_1 = new QThread(this);
    connect(this,SIGNAL(destroyed()),thread_1,SLOT(quit()));

    res->moveToThread(thread_1);
    thread_1->start();

  //  connect(this,SIGNAL(finished()),this,SLOT(close()));

  //  connect(ui->pushButton_3,&QPushButton::pressed,this,&Reseacrher::on_pushButton_3_clicked);
   //connect(ui->pushButton_3,&QKeyEvent::key,this,&Blocker::on_pushButton_3_clicked);

  //  ui->centralwidget->moveToThread(thread_1);
  //  ui->pushButton_3->moveToThread(thread_2);


}
Reseacrher::Reseacrher(QObject*){

}

Blocker::~Blocker()
{
    delete ui;
}



QString Blocker::allFiles = "";


void Blocker::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    ui->textBrowser->setText(currentFile);
    allFiles += currentFile + "\n";
    ui->textBrowser_2->setText(allFiles);

    file.close();

}

void Blocker::about(){
    QMessageBox::about(this, tr("About MDI"),
                 tr("Этот <b>Blocker</b> блокирует выбранное приложение и не дает его запустить." ));
}

void Blocker::on_pushButton_2_clicked()
{


    QString makeFile;

    makeFile.clear();

    for(int i=0; i < currentFile.size();i++){
        makeFile += currentFile[i];
        if(currentFile[i] == '/'){
            makeFile.clear();
        }
    }


    QMessageBox msgBox;
    msgBox.setWindowTitle("Сообщение о состоянии");


  /*
    if(IsProcessRun((wchar_t*)currentFile.utf16())){
      //  qDebug() << "Приложение уже запущено \n";
        msgBox.setText("Приложение уже запущено");
        msgBox.exec();

    }else{
       // qDebug() << "Приложение не запущено \n";
        msgBox.setText("Приложение не запущено");
        msgBox.exec();

    }
    */


    /**Если приложение уже запущено, проходим по списку и если данное приложение есть в списке завершаем его! */

}


bool Blocker:: IsProcessRun(wchar_t *ExeName)
{
   HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   if( hSnapshot == INVALID_HANDLE_VALUE )
    {
      qDebug() << "\nERROR hSnapshot \n";
      return( FALSE );
    }


   PROCESSENTRY32 pe;
   pe.dwSize = sizeof(PROCESSENTRY32);


   if( !Process32First( hSnapshot, &pe ) )
    {

      qDebug() << "\nERROR Process32First \n";
      CloseHandle( hSnapshot );
      return( FALSE );
   }

   Process32First(hSnapshot, &pe);


   while (1) {

      // std::wcout <<L"\nPROCESS NAME: "<< pe.szExeFile << L" == " <<  ExeName;
      if (wcscmp(pe.szExeFile, ExeName) == 0) {

         HANDLE ps = OpenProcess(1, false,  pe.th32ProcessID);
        //  ps = OpenProcess(1, false,  pe.th32ProcessID);

         if(TerminateProcess(ps,NULL) == 0){
             qDebug() << "\n==Some PROBLEMS==\n";
         }




          return true;
      }
      if (!Process32Next(hSnapshot, &pe)) return false;
   }
}


bool Reseacrher:: IsProcessRun(wchar_t *ExeName)
{
   HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   if( hSnapshot == INVALID_HANDLE_VALUE )
    {
      qDebug() << "\nERROR hSnapshot \n";
      return( FALSE );
    }


   PROCESSENTRY32 pe;
   pe.dwSize = sizeof(PROCESSENTRY32);


   if( !Process32First( hSnapshot, &pe ) )
    {

      qDebug() << "\nERROR Process32First \n";
      CloseHandle( hSnapshot );
      return( FALSE );
   }

   Process32First(hSnapshot, &pe);


   while (1) {

      // std::wcout <<L"\nPROCESS NAME: "<< pe.szExeFile << L" == " <<  ExeName;
      if (wcscmp(pe.szExeFile, ExeName) == 0) {

         HANDLE ps = OpenProcess(1, false,  pe.th32ProcessID);
        //  ps = OpenProcess(1, false,  pe.th32ProcessID);

         if(TerminateProcess(ps,NULL) == 0){
             qDebug() << "\n==Some PROBLEMS==\n";
         }




          return true;
      }
      if (!Process32Next(hSnapshot, &pe)) return false;
   }
}


void Blocker::on_pushButton_3_clicked()
{
    QVector<QString> programs = allFiles.split('\n');
    if(ui->pushButton_3){
        qDebug() << "Checked";
        emit finished();
    }

  //  emit start(programs);
}

void Reseacrher::run(QVector<QString> programs, bool x)
{

    while(x){
    //if(x){
            int counter = 0;
            QString makeFile;

            makeFile.clear();

            for(const auto &el : programs){
                if(el != ""){

                    for(int i=0; i < el.size();i++){
                        makeFile += el[i];
                        if(el[i] == '/'){
                            makeFile.clear();
                        }
                    }

                   qDebug() << el << " " << makeFile;
                   if(IsProcessRun((wchar_t*)makeFile.utf16()) == false){
                       counter++;
                   }else{

                   }




                }
            }
            //qDebug() << counter << " == " << programs.size();
            if(counter == programs.size() - 1)break;
        }

       // }
}

void Blocker:: keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Q:
            qDebug() << "Q";
            break;
    }
}


void Blocker::on_checkBox_stateChanged()
{
     QVector<QString> programs = allFiles.split('\n');

     if(ui->checkBox->isChecked()){
         emit start(programs,true);
        // QThread::sleep(1000);
     }



}

