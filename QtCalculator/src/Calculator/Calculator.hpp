#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP
#include <QtWidgets>
#include <format>


class Calculator : public QWidget {
Q_OBJECT
private: 
	QString inputValue;
	QStack<QString> stackResualts;
	QLCDNumber* infoLabel;
	QPushButton* createButton(const QColor& color, const QString& title, size_t width, size_t height);
	void calculate();
public:
	Calculator(QWidget* parent);
	~Calculator() = default;
public slots:
	void slotButtonClicked();
signals:
};


#endif // CALCULATOR_HPP
