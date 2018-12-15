#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>

#include "ui_mainwindow.h"

//namespace Ui {	class MainWindow;  }

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

	QPushButton *skillBtn[35];
	QLabel *skillLbl[35];

private:
	//Ui::MainWindow *ui;
	Ui::MainWindowClass ui;
};
