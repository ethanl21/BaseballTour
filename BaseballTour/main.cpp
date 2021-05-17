#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QFontDatabase>

QByteArray readTextFile(const QString &file_path) {
  QFile input_file(file_path);
  QByteArray input_data;

  if (input_file.open(QIODevice::Text | QIODevice::Unbuffered | QIODevice::ReadOnly)) {
    input_data = input_file.readAll();
    input_file.close();
    return input_data;
  }
  else {
    return QByteArray();
  }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString style_sheet = readTextFile(":/stylesheets/MaterialDark.qss");
    a.setStyleSheet(style_sheet);
    QFontDatabase::addApplicationFont(":/font/Roboto.ttf");
    QFont roboto("Roboto", 12);
    a.setFont(roboto);

    MainWindow w;
    w.show();

    return a.exec();
}
