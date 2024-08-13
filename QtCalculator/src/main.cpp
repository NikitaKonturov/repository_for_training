#include <iostream>
#include <QtWidgets>
#include <QDebug>
#include <chrono>
#include "Calculator/Calculator.hpp"


int main(int args, char** argv) 
{
	
	QApplication* calculator = new QApplication(args, argv);
	
	QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath() + "/platforms");

	
	calculator->setWindowIcon(QIcon("../../Calculator/Calculator/Calculator_31111.ico"));


	Calculator calcul(nullptr);
	calcul.setWindowTitle("Calculator");
	calcul.resize(230, 200);
	
	calcul.show();

	return calculator->exec();
}