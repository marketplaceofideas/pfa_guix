#ifndef MISCWINDOWS_H
#define MISCWINDOWS_H

#include <QtWidgets>
#include "npc.h"

class IndexWindow : public QDialog
{
	Q_OBJECT

public:
	IndexWindow(QString keyName, QVector<QString> &vec, QWidget *parent = Q_NULLPTR)
	{
		this->resize(430, 800);
		QVBoxLayout *mainLayout = new QVBoxLayout(this);
		//mainLayout->setContentsMargins(0, 0, 0, 0);

		QScrollArea *scroll = new QScrollArea(this);
		scroll->setWidgetResizable(true);
		scroll->QAbstractScrollArea::setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		scroll->horizontalScrollBar()->setEnabled(false);

		QWidget *page = new QWidget();
		QFormLayout *layout = new QFormLayout(page);
		//layout->setLabelAlignment(Qt::AlignRight);

		//////////////////////////////////////////////////////////////////////////

		if (keyName.right(4) == ".txt")
			keyName = keyName.left(keyName.size() -  4);
		QStringList key = Frame::getQString(keyName + "Key");
		QStringList fileKey = Frame::getQString(keyName + "File");
		vec.resize(fileKey.size());

		layout->addRow("                                ", new QFrame(page));
		// key[i]: _e_Label (;index;nameKey)
		for (int i = 0; i < key.length(); ++i)
		{
			if (Frame::getQString("skill").contains(key[i])) // change value to skill, each change splits the vector, sets the val, and recombines (track nums with var for dynamic)
			{
				int fileIndex = fileKey.indexOf(key[i]);
				if (key[i] == "Craft" || key[i] == "Perform" || key[i] == "Profession")
				{
					for (int j = 0; j < 5; ++j)
					{
						for (int k = 0; k < Frame::getQString(key[i].toLower()).length() - 1; ++k)
							vec[fileIndex] += ",";
						if (j != 4)
							vec[fileIndex] += ";";
					}
					key[i] = "k;2,4.5;" + key[i];
				}
				else
				{
					key[i] = "m;2,4.5;" + key[i];
				}
			}

			QStringList temp = key[i].split(';'); // _s_;rowNum; Label1, 2, 3; nameKey1, 2, 3
			int fileIndex = fileKey.indexOf(temp[2]);

			char typeVal = key[i][0].unicode();
			int rowIndex = temp[1].toInt();

			if (typeVal == 'd')
				vec[fileIndex] += ",";

			if (rowIndex == 1 || typeVal == 'm') // single row allocation
			{
				QString qs = typeVal;
				qs += ";" + temp[1];
				if (key[i][0].unicode() == 'f')
					layout->addRow(widgetSetter(qs, vec, fileIndex, page));
				else
					layout->addRow(temp[2], widgetSetter(qs + ";" + temp[2], vec, fileIndex, page));
			}

			else if (rowIndex == 0 || typeVal == 'k') // dynamic allocation using button
			{
				QFrame *newFrame = new QFrame(page);
				QFormLayout *newLayout = new QFormLayout(newFrame);
				newLayout->setContentsMargins(0, 0, 0, 0);
				if (typeVal != 'k')
					temp[1] = "1";

				newLayout->addRow("                                ", new QFrame(newFrame));
				newLayout->addRow(temp[2], widgetSetter(temp.join(";"), vec, fileIndex, newFrame));

				QPushButton *newButton = new QPushButton("Add", page);
				connect(newButton, &QPushButton::clicked, [=, &vec] {
					if (typeVal != 'k')
						vec[fileIndex] += ";";
					if (typeVal == 'd')
						vec[fileIndex] += ",";
					QString qs = key[i].split(";")[0] + ";";
					if (typeVal == 'k')
						qs += temp[1] + ";" + key[i].split(";")[2];
					else
						qs += QString::number(newLayout->rowCount() - 2) + ";" + key[i].split(";")[2];
					newLayout->insertRow(newLayout->rowCount() - 2, "", widgetSetter(qs, vec, fileIndex, newFrame));
				});
				newLayout->addRow("&", newButton);

				newLayout->addRow("                                ", new QFrame(newFrame));
				layout->addRow(newFrame);
			}
			
			else // multiple allocation
			{
				QStringList labels = temp[3].split(',');
				//QStringList nameKeys = temp[3].split(",");
				for (int j = 0; j < rowIndex; ++j)
				{
					QString qs = typeVal;
					qs += ";" + QString::number(j + 1);
					if (j != rowIndex - 1)
					{
						vec[fileIndex] += ";";
						if (typeVal == 'd')
							vec[fileIndex] += ",";
					}
					if (key[i][0].unicode() == 'f')
						layout->addRow(widgetSetter(qs, vec, fileIndex, page));
					else
						layout->addRow(labels[j], widgetSetter(qs + ";" + labels[j], vec, fileIndex, page));
				}
			}

			if (temp[2] == "Size")
				vec[fileIndex] += ";";
		}
		layout->addRow("                                ", new QFrame(page));

		// treasure ?

		// more

		//////////////////////////////////////////////////////////////////////////

		QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
			| QDialogButtonBox::Cancel, page);

		connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
		connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);


		scroll->setWidget(page);
		mainLayout->addWidget(scroll);
		mainLayout->addWidget(buttonBox);
		setWindowTitle("Add NPC");
	}

	static QWidget *widgetSetter(QString key, QVector<QString> &vec, int vecIndex, QWidget *page)
	{
		QStringList temp = key.split(";"); // _s_;rowNum; Label1, 2, 3; nameKey1, 2, 3

		char typeVal = key[0].unicode();
		QStringList tempRow = temp[1].split(".");
		QStringList rowIndexes = tempRow[0].split(",");
		int rowSize = tempRow[tempRow.length() - 1].toInt();

		switch (typeVal) // hey bud, add label type for specifications and shit
		{
			case 'e': // edit (lineedit)
			{
				QLineEdit *newEdit = new QLineEdit(page);
				connect(newEdit, &QLineEdit::textChanged, [=, &vec] {
					QStringList vecSplit = vec[vecIndex].split(";");
					vecSplit[rowSize - 1] = newEdit->text();
					vec[vecIndex] = vecSplit.join(";");
				});
				return newEdit;
			}

			case 'n': // number (spinbox)
			{
				QSpinBox *newSpin = new QSpinBox(page);
				newSpin->setRange(-10000000, 10000000);
				connect(newSpin, qOverload<int>(&QSpinBox::valueChanged), [=, &vec] {
					QStringList vecSplit = vec[vecIndex].split(";");
					vecSplit[rowSize - 1] = QString::number(newSpin->value());
					vec[vecIndex] = vecSplit.join(";");
				});
				return newSpin;
			}

			case 'm': // multiple (spinboxes)
			{
				QFrame *newFrame = new QFrame(page);
				QHBoxLayout *newLayout = new QHBoxLayout(newFrame);
				newLayout->setContentsMargins(0, 0, 0, 0);

				for (int i = 0; i < rowSize; ++i)
				{
					if (i != rowSize - 1)
						vec[vecIndex] += ";";
					if (tempRow.length() == 1 || rowIndexes.contains(QString::number(i+1)))
					{
						QSpinBox *newSpin = new QSpinBox(page);
						newSpin->setRange(-10000000, 10000000);
						newSpin->setMinimumWidth(40);
						connect(newSpin, qOverload<int>(&QSpinBox::valueChanged), [=, &vec] {
							QStringList vecSplit = vec[vecIndex].split(";");
							vecSplit[i] = QString::number(newSpin->value());
							vec[vecIndex] = vecSplit.join(";");
						});
						newLayout->addWidget(newSpin);
					}
				}
				return newFrame;
			}

			case 's': // selector (combobox)
			{
				QComboBox *newCombo = new QComboBox(page);
				newCombo->addItem("");
				QStringList tempNames = Frame::getQString(temp[2].toLower()); // combo values
				for (int k = 0; k < tempNames.length(); ++k)
				{
					newCombo->addItem(tempNames[k]);
				}
				connect(newCombo, qOverload<int>(&QComboBox::currentIndexChanged), [=, &vec] {
					QStringList vecSplit = vec[vecIndex].split(";");
					vecSplit[rowSize - 1] = newCombo->currentText();
					vec[vecIndex] = vecSplit.join(";");
				});
				newCombo->setCurrentIndex(0);
				return newCombo;
			}

			case 'd': // double (combobox + spinbox)
			{
				QFrame *newFrame = new QFrame(page);
				QHBoxLayout *newLayout = new QHBoxLayout(newFrame);
				newLayout->setContentsMargins(0, 0, 0, 0);

				QComboBox *newCombo = new QComboBox(page);
				newCombo->addItem("");
				QStringList tempNames = Frame::getQString(temp[2].toLower()); // combo values
				for (int k = 0; k < tempNames.length(); ++k)
				{
					newCombo->addItem(tempNames[k]);
				}
				connect(newCombo, qOverload<int>(&QComboBox::currentIndexChanged), [=, &vec] {
					QStringList vecSplit = vec[vecIndex].split(";");
					QStringList vecSplitSplit = vecSplit[rowSize - 1].split(",");
					vecSplitSplit[0] = newCombo->currentText();
					vecSplit[rowSize - 1] = vecSplitSplit.join(",");
					vec[vecIndex] = vecSplit.join(";");
				});
				newCombo->setCurrentIndex(0);

				QSpinBox *newSpin = new QSpinBox(page);
				newSpin->setRange(-10000000, 10000000);
				connect(newSpin, qOverload<int>(&QSpinBox::valueChanged), [=, &vec] {
					QStringList vecSplit = vec[vecIndex].split(";");
					QStringList vecSplitSplit = vecSplit[rowSize - 1].split(",");
					vecSplitSplit[1] = QString::number(newSpin->value());
					vecSplit[rowSize - 1] = vecSplitSplit.join(",");
					vec[vecIndex] = vecSplit.join(";");
				});

				newLayout->addWidget(newCombo);
				newLayout->addWidget(newSpin);
				return newFrame;
			}

			case 'k': // special skills (combobox + multiple)
			{
				QFrame *newFrame = new QFrame(page);
				QHBoxLayout *newLayout = new QHBoxLayout(newFrame);
				newLayout->setContentsMargins(0, 0, 0, 0);

				QComboBox *newCombo = new QComboBox(page);
				//newCombo->setMaximumWidth(80);
				newCombo->addItem("");
				QStringList tempNames = Frame::getQString(temp[2].toLower()); // combo values
				for (int k = 0; k < tempNames.length(); ++k)
				{
					newCombo->addItem(tempNames[k]);
				}
				newCombo->setCurrentIndex(0);
				newLayout->addWidget(newCombo);

				for (int i = 0; i < rowSize; ++i)
				{
					if (tempRow.length() == 1 || rowIndexes.contains(QString::number(i+1)))
					{
						QSpinBox *newSpin = new QSpinBox(page);
						newSpin->setRange(-10000000, 10000000);
						newSpin->setMinimumWidth(40);
						connect(newSpin, qOverload<int>(&QSpinBox::valueChanged), [=, &vec] {
							QStringList vecSplit = vec[vecIndex].split(";");
							QStringList vecSplitSplit = vecSplit[i].split(",");
							vecSplitSplit[newCombo->currentIndex() - 1] = QString::number(newSpin->value());
							vecSplit[i] = vecSplitSplit.join(",");
							vec[vecIndex] = vecSplit.join(";");
						});
						newLayout->addWidget(newSpin);
					}
				}
				return newFrame;
			}

			case 'f':
			{
				QFrame *newFrame = new QFrame(page);
				return newFrame;
				break;
			}
		}
	}
};

#endif // MISCWINDOWS_H
