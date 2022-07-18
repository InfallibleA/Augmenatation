#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <QProcess>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <filesystem>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string.hpp>

//#pragma comment(lib, "user32.lib")
//#pragma comment(lib, "advapi32.lib")

using namespace std;
namespace bsfs = boost::filesystem;
using namespace bsfs;
using namespace cv;

//КЛАСС
class Augmentation{
    stringstream ss; // буфер для перевода из int в string для имени файла
    int a = 0; // помогает формировать имя файла
    Mat editimg;
    Mat img;
    Mat imgNal2;
    Mat imgEdit;
  public:
     string path1, path2,pathonemore, str;
     string* AS;
     string* AS2;
     string pathforsaving;
     path path;
     Mat imgNal;
     int checknumbox1;
     int checknumbox2;
     int checknumbox3;
     int checknumbox4;
     int checknumbox5;
     int checknumbox6;
     int checknumbox7;
     int count = 1;
     int i = 0;
     int i1 = 0;
     double alpha = 0.5;
     double beta;
     double angle = 0.0;
     double scale = 1.0;

     void augmentation(Mat kek){
         img = kek;
         pathforsaving = "";
         //Определённые манипуляции с именем файла
         ss << a;
         str = ss.str();
         string format = ".jpg";
         pathforsaving = path2 + str + format;
         //cout << pathforsaving << endl;
         //Конец манипуляциям

         // обесцвечивание
        if(checknumbox1 == 1){ // a
         cvtColor(img, imgEdit, COLOR_BGR2GRAY);
         imwrite(pathforsaving,imgEdit);
         imgEdit.release();
         }

         //Определённые манипуляции с именем файла
         ss.str("");
         a = a + 1;
         ss << a;
         str = ss.str();
         pathforsaving = path2 + str + format;
         // Конец манипуляциям

         // изменение по вертикали
         if(checknumbox2 == 1){ // b
         flip(img, imgEdit, -1);
         imwrite(pathforsaving,imgEdit);
         imgEdit.release();
         }

         //Определённые манипуляции с именем файла
         ss.str("");
         a = a + 1;
         ss << a;
         str = ss.str();
         pathforsaving = path2 + str + format;
         // Конец манипуляциям

         // изменение по горизонтали
         if(checknumbox3 == 1){ // c
         flip(img, imgEdit, 1);
         imwrite(pathforsaving,imgEdit);
         imgEdit.release();
         }
         //Определённые манипуляции с именем файла
         ss.str("");
         a = a + 1;
         ss << a;
         str = ss.str();
         pathforsaving = path2 + str + format;
         // Конец манипуляциям

         // ресайз
         if(checknumbox4 == 1){ //d
         cv::resize(img, imgEdit,Size(), 0.1,0.1,INTER_LINEAR);
         imwrite(pathforsaving,imgEdit);
         imgEdit.release();
         }

         //Определённые манипуляции с именем файла
         ss.str("");
         a = a + 1;
         ss << a;
         str = ss.str();
         pathforsaving = path2 + str + format;
         // Конец манипуляциям

         // наложение одного изображения на другое
         if(checknumbox5 == 1){ //e
             if(alpha > 1.0){
                 alpha = 1.0;
             }
         cv::resize(imgNal, imgNal2,Size(img.size().width,img.size().height),INTER_LINEAR);// ресайз
         beta = (1.0 - alpha);
         cv::addWeighted(img, alpha, imgNal2, beta, 0.0, imgEdit);
         imwrite(pathforsaving,imgEdit);
         imgEdit.release();
         }
         //Определённые манипуляции с именем файла
         ss.str("");
         a = a + 1;
         ss << a;
         str = ss.str();
         pathforsaving = path2 + str + format;
         // Конец манипуляциям

         //поворот\наклон
         if(checknumbox6 == 1){//f
             if(angle > 360){
                 angle = 360;
             }
         imgEdit = Mat::zeros( img.rows, img.cols, img.type() );
         Point2f center(img.cols/2, img.rows/2);
         Mat MM = cv::getRotationMatrix2D(center, angle, scale);
         cv::warpAffine(img,imgEdit, MM, img.size());
         imwrite(pathforsaving,imgEdit);
         imgEdit.release();
         }
         //Определённые манипуляции с именем файла
         ss.str("");
         a = a + 1;
         ss << a;
         str = ss.str();
         pathforsaving = path2 + str + format;
         // Конец манипуляциям

         //обрезание изображения
         if(checknumbox7 == 1){//f
         int imgheight = img.rows; // y
         int imgwidth = img.cols; //x

             // это 1/4
         int X1 = 0;
         int Y1 = 0;
         int X2 = imgwidth / 2 - X1;
         int Y2 = imgheight / 2 - Y1;

         Rect croppedImageFirst(X1, Y1, X2,Y2);
         imgEdit = img(croppedImageFirst);
         imwrite(pathforsaving,imgEdit);
         imgEdit.release();

         ss.str("");
         a = a + 1;
         ss << a;
         str = ss.str();
         pathforsaving = path2 + str + format;

             // это 2/4
         X1 = imgwidth / 2;
         Y1 = 0;
         X2 = imgwidth - X1;
         Y2 = imgheight / 2 - Y1;

         Rect croppedImageSecond(X1, Y1, X2,Y2);
         imgEdit = img(croppedImageSecond);
         imwrite(pathforsaving,imgEdit);
         imgEdit.release();

         ss.str("");
         a = a + 1;
         ss << a;
         str = ss.str();
         pathforsaving = path2 + str + format;

             // это 3/4
         X1 = 0;
         Y1 = imgheight / 2;
         X2 = imgwidth / 2 - X1;
         Y2 = imgheight / 2;

         Rect croppedImageThird(X1, Y1, X2,Y2);
         imgEdit = img(croppedImageThird);
         imwrite(pathforsaving,imgEdit);
         imgEdit.release();

         ss.str("");
         a = a + 1;
         ss << a;
         str = ss.str();
         pathforsaving = path2 + str + format;

             // это 4/4
         X1 = imgwidth / 2;
         Y1 = imgheight / 2;
         X2 = imgwidth - X1;
         Y2 = imgheight - Y1;

         Rect croppedImageFourth(X1, Y1, X2,Y2);
         imgEdit = img(croppedImageFourth);
         imwrite(pathforsaving,imgEdit);
         imgEdit.release();
         }
     }
};
//КЛАСС

Augmentation objNames;
//ФУНКЦИИ

void MainWindow::checkallnumbox(){

    if(ui->checkBox->isChecked()){ //a
        objNames.checknumbox1 =  1;
    }else objNames.checknumbox1 =  0;

        if(ui->checkBox_2->isChecked()){ //b
            objNames.checknumbox2 = + 1;
        }else objNames.checknumbox2 =  0;

            if(ui->checkBox_3->isChecked()){ //c
                objNames.checknumbox3 =  1;
            }else objNames.checknumbox3 =  0;

                if(ui->checkBox_4->isChecked()){ //d
                    objNames.checknumbox4 =  1;
                }else objNames.checknumbox4 =  0;

                    if(ui->checkBox_5->isChecked()){ //e
                        objNames.checknumbox5 =  1;
                    }else objNames.checknumbox5 =  0;

                        if(ui->checkBox_6->isChecked()){ //f
                            objNames.checknumbox6 =  1;
                        }else objNames.checknumbox6 =  0;

                            if(ui->checkBox_7->isChecked()){ //g
                                objNames.checknumbox7 =  1;
                            }else objNames.checknumbox7 =  0;
}


//отчистить всё
void clearitall(){
    objNames.path1.clear();
    objNames.path2.clear();
    objNames.pathonemore.clear();
    objNames.str.clear();
    delete[] objNames.AS;
    objNames.pathforsaving.clear();
    objNames.path.clear();
     objNames.checknumbox1 = 0;
     objNames.checknumbox2 = 0;
     objNames.checknumbox3 = 0;
     objNames.checknumbox4 = 0;
     objNames.checknumbox5 = 0;
     objNames.checknumbox6 = 0;
     objNames.checknumbox7 = 0;
     objNames.count = 1;
     objNames.scale = 1.0;
}

void MainWindow::checkWorkingButton(){ //проверка на открытия кнопки Выполнить
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty()){
        ui->pushButton_4->setEnabled(false);
    }
    else{
        ui->pushButton_4->setEnabled(true);
    }
};


void MainWindow::checkSaveButton(){ //проверка на открытия кнопки
    if(ui->lineEdit->text().isEmpty()){
        ui->pushButton_2->setEnabled(false);
    }
    else{
        ui->pushButton_2->setEnabled(true);
    }
};

void  getFoldersize(string rootFolder,double & file_size){ //сколько весит директория

    boost::replace_all(rootFolder, "\\\\", "\\");
    path folderPath(rootFolder);

    if (bsfs::exists(folderPath)){
        bsfs::directory_iterator end_itr;

        for (bsfs::directory_iterator dirIte(rootFolder); dirIte != end_itr; ++dirIte )
        {
            bsfs::path filePath(dirIte->path());
            try{
                if (!bsfs::is_directory(dirIte->status()) )
                {
                    file_size = file_size + bsfs::file_size(filePath);
                }else{
                    getFoldersize(filePath.string(),file_size);
                }
            }catch(exception& e){
                cout << e.what() << endl;
            }
        }
    }
}

//ФУНКЦИИ

//ПРОГРАММА
MainWindow::MainWindow(QWidget  *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItem("Случайное число");
    ui->comboBox->addItem("Заданное значение");
    ui->comboBox->setEnabled(false);
    ui->lineEdit_5->setReadOnly(true);
    ui->pushButton_7->setEnabled(false);
    ui->lineEdit_6->setReadOnly(true);
    ui->pushButton_5->setEnabled(false);

    checkSaveButton();
    checkWorkingButton();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Выбрать файл
void MainWindow::on_pushButton_clicked()
{
   ui->lineEdit_3->clear();
   QFileDialog dialog(this);
   dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
   dialog.setViewMode(QFileDialog::Detail);
   QString fileName = QFileDialog::getExistingDirectory();

   if (!fileName.isEmpty()){
       objNames.path1 = fileName.toLocal8Bit().constData();
       //cout << objNames.path1 << endl;
       ui->lineEdit->setText(fileName);
       fileName.clear();
       double file_size = 0;
       string buffernumber = "";
       getFoldersize(objNames.path1,file_size);
       file_size = (file_size / 1024 / 1024);
       buffernumber = to_string(file_size);
       QString megabite = QString::fromStdString(buffernumber);
       ui->lineEdit_3->setText(megabite);
       megabite.clear();

       checkSaveButton();
       checkWorkingButton();
   }
}

//Куда сохранить
void MainWindow::on_pushButton_2_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images ()"));
    dialog.setViewMode(QFileDialog::Detail);
    QString savefileName = QFileDialog::getSaveFileName(this,tr("Save Images (*.jpg *.xpm *.png)"), "C:/", tr("Image Files "));

    if(!savefileName.isEmpty()){
        objNames.path2 = "";
        objNames.path2 = savefileName.toLocal8Bit().constData();
        ui->lineEdit_2->setText(savefileName);
        savefileName.clear();
    }
    checkWorkingButton();
}

// НАЛОЖЕНИЕ ИЗОБРАЖЕНИЯ
void MainWindow::on_pushButton_5_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Изображение для наложения  ()"));
    dialog.setViewMode(QFileDialog::Detail);
    QString editimagefileName = QFileDialog::getOpenFileName(this,tr("Выбрать изображение для наложения "), "C:/");

    if(!editimagefileName.isEmpty()){
    objNames.pathonemore = editimagefileName.toLocal8Bit().constData();
    objNames.imgNal = imread(objNames.pathonemore);

    ui->lineEdit_4->setText("Выбрано");

    editimagefileName.clear();
    }
    else
    ui->lineEdit_4->text().isEmpty();
}

//Выполнить
void MainWindow::on_pushButton_4_clicked()
{
    string s;
    int maxsrc = 0;
    objNames.AS = new string[objNames.count];
    checkallnumbox();

        // ТУТ Я РАБОТАЮ С ФАЙЛОВОЙ СИСТЕМОЙ ОТКУДА В РАМКАХ МАССИВА ПЕРЕДАЮТСЯ ПУТИ ФАЙЛОВ
    for (auto& p : directory_iterator(objNames.path1))
        {
            path multipath;
            multipath = p;
            maxsrc++;
            s = multipath.generic_string();
            if (s != "") {
              objNames.count++;
              objNames.AS2 = new string[objNames.count];

              for (int i = 1; i < objNames.count - 1; i++)
                    objNames.AS2[i] = objNames.AS[i];

              objNames.AS2[objNames.count - 1] = s;

                if (objNames.AS != nullptr)
                    delete[] objNames.AS;

                objNames.AS = objNames.AS2;
            }
        }
    // ПРОВЕРКА
    /*
    cout << "\nFolder files:\n";
       if (objNames.count > 0)
           for (int i = 1; i < objNames.count; i++)
               cout << "AS[" << i << "] = " << objNames.AS[i] << ::endl;
       else
            cout << "array AS is empty.";
        */
    //ПРОВЕРКА
        // ТУТ Я РАБОТАЮ С ФАЙЛОВОЙ СИСТЕМОЙ ОТКУДА В РАМКАХ МАССИВА ПЕРЕДАЮТСЯ ПУТИ ФАЙЛОВ
       if(objNames.count > 0){
          for(int i = 1; i < objNames.count; i ++){
           Mat doimg = imread(objNames.AS[i]);
           objNames.augmentation(doimg); // кидаем путь КАРТИНКИ в функцию
           ui->progressBar->setMinimum(0); // прогресс работы
           ui->progressBar->setMaximum(maxsrc);
           ui->progressBar->setValue(i);
    }
  }
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    QMessageBox msgBox;

    QString NotifyPath = QString::fromStdString(objNames.path2);
    msgBox.setText("Обработанно");
    msgBox.setInformativeText("Место хранения - " + NotifyPath);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.exec();
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    NotifyPath.clear();
    clearitall();

}

void MainWindow::on_checkBox_5_clicked() // проверка на прозрачность чекбокс
{
    objNames.i1 = objNames.i1 + 1;
    if(objNames.i1 == 1){
    ui->pushButton_5->setEnabled(true);
    ui->lineEdit_6->setReadOnly(false);
     ui->pushButton_7->setEnabled(true);
     ui->lineEdit_6->setValidator( new QIntValidator(0, 100, this) );
    }
    else{
        ui->lineEdit_4->setText("");
        ui->lineEdit_6->setText("");
        ui->pushButton_5->setEnabled(false);
        ui->lineEdit_6->setReadOnly(true);
        ui->pushButton_7->setEnabled(false);
        objNames.i1 = objNames.i1 - 2;
    }
}

void MainWindow::on_checkBox_6_clicked() //поврот наклон чекбокс
{
    objNames.i = objNames.i + 1;
    if(objNames.i == 1){
    ui->comboBox->setEnabled(true);
    }
    else{
            ui->comboBox->setEnabled(false);
            ui->lineEdit_5->setReadOnly(true);
            ui->pushButton_6->setEnabled(false);
            objNames.i = objNames.i - 2;
    }
}

void MainWindow::on_pushButton_3_clicked() //выход
{
    QApplication::quit();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg) // если меняется с рандома на задаанное значение
{
    if(ui->comboBox->currentText() == "Заданное значение"){
        ui->pushButton_6->setEnabled(true);
        ui->lineEdit_5->setReadOnly(false);
        ui->lineEdit_5->setValidator( new QIntValidator(0, 100, this) );
    }
    else
    {
        ui->lineEdit_5->setReadOnly(true);
        ui->pushButton_6->setEnabled(false);
        ui->lineEdit_5->clear();
        srand(time(0));
        objNames.angle = 1 + rand() % 360;
    }
}

void MainWindow::on_pushButton_7_clicked() // ПРОЗРАЧНОСТЬ
{
    QMessageBox msgBox;
     QString xLineEdit = ui->lineEdit_6->text();
     double invisbuffer = xLineEdit.toInt();
     if(!xLineEdit.isEmpty()){
     objNames.alpha = (100 - invisbuffer) * 0.01;

     msgBox.setText("Новые значения успешно установлены");
     msgBox.setStandardButtons(QMessageBox::Ok);
     msgBox.setDefaultButton(QMessageBox::Cancel);
     msgBox.exec();
     }
     else {
    msgBox.setText("Значения не заданы");
    msgBox.setInformativeText("Поле уровня прозрачности не должно быть пустым");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.exec();
}
}

void MainWindow::on_pushButton_6_clicked() //поврот наклон задать градус
{
    QMessageBox msgBox;
    QString xLineEdit = ui->lineEdit_5->text();
    int anglebuffer = xLineEdit.toInt();
    if(!xLineEdit.isEmpty()){

    objNames.angle = anglebuffer;

    msgBox.setText("Новые значения успешно установлены");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.exec();
    }
    else {
        msgBox.setText("Значения не заданы");
        msgBox.setInformativeText("Поле <<Градус>> не должно быть пустым");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        msgBox.exec();
    }
}

//ПРОГРАММА
