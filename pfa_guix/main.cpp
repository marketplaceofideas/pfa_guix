#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qRegisterMetaType<std::string>("std::string");

	MainWindow w;
	w.show();
	return a.exec();
}
