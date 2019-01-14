#pragma once

#include <QtWidgets/QMainWindow>
//#include <QVector>
#include "ui_mainwindow.h"
#include "player.h"

#include <QtWidgets>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

	QStackedWidget *mainStk;
	QString pfilename;
	//QFile pfile;

	bool pflag;
	Player *player0;
	//void 

private:
	Ui::MainWindowClass ui;

public slots:
	void openPlayer();
};
