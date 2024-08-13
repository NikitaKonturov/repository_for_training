#include "Calculator.hpp"


QPushButton* Calculator::createButton(const QColor& color, const QString& title, size_t width = 40, size_t height = 40)
{
	QPushButton* button = new QPushButton(title);

	button->setMinimumSize(width, height);
	this->connect(button, &QPushButton::clicked, this, &Calculator::slotButtonClicked);

	button->setStyleSheet(QString(std::format("background-color: rgb({}, {}, {}); color: rgb(255, 255, 255);", color.red(), color.green(), color.blue()).c_str()));

	return button;
}

Calculator::Calculator(QWidget* parent = nullptr) : QWidget(parent)
{
	this->infoLabel = new QLCDNumber(12);
	this->infoLabel->setSegmentStyle(QLCDNumber::Flat);
	this->infoLabel->setMinimumSize(150, 50);

	this->infoLabel->setStyleSheet(
		"QLCDNumber {"
		"	background-color: #99FFCC;"
		"	color: #000000;"
		"	border: 3px solid red;"
		"	border-radius: 0px;"
		"	font-size: 30px;"
		"}"
	);



	QPalette mainPalette;

	mainPalette.setColor(QPalette::Window, QColor(105, 243, 26));
	
	this->setAutoFillBackground(true);
	this->setAttribute(Qt::WA_StyledBackground, true);
	this->setPalette(mainPalette);

	QChar inputButtons[4][4] = {{'7','8','9', '/'}, 
								{'4','5','6', '*'}, 
								{'1','2','3', '-'}, 
								{'0','.','=', '+'}, 
							    };
	QGridLayout* mainLayout = new QGridLayout(parent);

	mainLayout->addWidget(infoLabel, 0, 0, 1, 4);

	//mainLayout->addWidget(this->createButton("RES", 40, 30), 1, 2);
	mainLayout->addWidget(this->createButton(QColor(255, 0, 0), "CE", 40, 30), 1, 3);

	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; j++) {
			mainLayout->addWidget(this->createButton(QColor(102, 14, 14), inputButtons[i][j]), i + 2, j);
		}
	}

	setLayout(mainLayout);

}

void Calculator::slotButtonClicked()
{
	QString senderName = qobject_cast<QPushButton*>(sender())->text();

	if (senderName == "CE") {
		this->infoLabel->display("0");
		this->stackResualts.clear();
		this->inputValue.clear();
		return;
	} 

	if (senderName.contains(QRegularExpression("[0-9]"))) {
		this->inputValue.push_back(senderName);
		this->infoLabel->display(inputValue.toDouble());
	}
	else if (senderName == ".") {
		this->inputValue.push_back(senderName);
		this->infoLabel->display(inputValue);
	}
	else {
		if (this->stackResualts.size() >= 2) {
			try {
				this->stackResualts.push(QString().setNum(this->infoLabel->value()));
				this->calculate();
				this->stackResualts.clear();
				this->stackResualts.push(QString().setNum(this->infoLabel->value()));
				if (senderName != "=") {
					this->stackResualts.push(this->inputValue);
				}
			}
			catch (std::invalid_argument &err) {
				this->stackResualts.clear();
				this->inputValue.clear();
				this->infoLabel->display("0");

				QString mess(err.what());

				QMessageBox::critical(this, "Error", mess);
			}      
		}
		else {
			this->stackResualts.push(QString().setNum(this->infoLabel->value()));
			this->stackResualts.push(senderName);
			this->inputValue.clear();
		}
	}
}
 
void Calculator::calculate() {
	double secondOperand = this->stackResualts.pop().toDouble();
	QString operation = this->stackResualts.pop();
	double firstOperand = this->stackResualts.pop().toDouble();
	double result = 0.0;


	if (operation == "*") {
		result = firstOperand * secondOperand;
	}

	if (operation == "+") {
		result = firstOperand + secondOperand;
	}
	if (operation == "-") {
		result = firstOperand - secondOperand;
	}
	if (operation == "/") {
		if (secondOperand == 0) {
			throw std::invalid_argument("Division by zero!!!");
		}
		result = firstOperand / secondOperand;
	}

	this->infoLabel->display(result);
}
