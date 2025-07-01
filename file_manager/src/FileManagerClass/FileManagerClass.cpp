#include "FileManagerClass.hpp"


void FileManagerClass::fullScreenSlot()
{
    QPushButton* fullScreenButton = dynamic_cast<QPushButton*>(this->sender());

    if(!this->isFullScreen()) {
        QPixmap smallWindowIcon("../sprites/smallWindowIcon.png");
        fullScreenButton->setIconSize(QSize(12, 12));
        fullScreenButton->setIcon(smallWindowIcon);
        this->saveGeometry = this->geometry();
        this->showFullScreen();
    }
    else {
        QPixmap fullScreenIcon("../sprites/fullscreenIcon2.png");
        fullScreenButton->setIconSize(QSize(15,15));
        fullScreenButton->setIcon(fullScreenIcon);
        this->showNormal();
        this->setGeometry(this->saveGeometry);
    }   
}


FileManagerClass::FileManagerClass(QApplication* app, QWidget* parent) : QWidget(parent)
{
    this->saveGeometry = this->geometry();
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowStaysOnTopHint);

    QWidget* leftPart = new QWidget(this);
    QWidget* rightPart = new QWidget(this);


    this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    


/*######################## Создание кнопок ########################*/ 

    QPushButton* exitButton = new QPushButton(this);
    QPushButton* fullScreenButton = new QPushButton(this);
    QPushButton* collapseButton = new QPushButton(this);

    exitButton->setMaximumSize(20, 20);
    fullScreenButton->setMaximumSize(20, 20);
    collapseButton->setMaximumSize(20, 20);

    QPixmap exitIcon("../sprites/exitIcon.png"); 
    exitButton->setIconSize(QSize(16, 16));
    exitButton->setIcon(exitIcon);
    
    QPixmap fullScreenIcon("../sprites/fullscreenIcon2.png");
    fullScreenButton->setIconSize(QSize(15, 15));
    fullScreenButton->setIcon(fullScreenIcon);

    QPixmap colapseIcon("../sprites/colapseIcon.png");
    collapseButton->setIconSize(QSize(15, 15));
    collapseButton->setIcon(colapseIcon);

    exitButton->setFlat(true);
    fullScreenButton->setFlat(true);
    collapseButton->setFlat(true);

    exitButton->setStyleSheet("QPushButton {background-color: #403f3e; border: 0px; border-radius: 10px;} QPushButton:hover{background-color: #4a4948; border: 0px; border-radius: 10px;}");
    fullScreenButton->setStyleSheet("QPushButton {background-color: #403f3e; border: 0px; border-radius: 10px;} QPushButton:hover{background-color: #4a4948; border: 0px; border-radius: 10px;}");    
    collapseButton->setStyleSheet("QPushButton {background-color: #403f3e; border: 0px; border-radius: 10px;} QPushButton:hover{background-color: #4a4948; border: 0px; border-radius: 10px;}");

    this->connect(exitButton, &QPushButton::clicked, app, &QApplication::quit);
    this->connect(fullScreenButton, &QPushButton::clicked, this, &FileManagerClass::fullScreenSlot);
    this->connect(collapseButton, &QPushButton::clicked, this, &FileManagerClass::showMinimized);
    
/*###############################################################*/

    QGridLayout* mainWindowLayout = new QGridLayout(this);
    mainWindowLayout->setContentsMargins(0, 0, 0, 0);
    mainWindowLayout->setSpacing(0);

    this->setLayout(mainWindowLayout);

    rightPart->setStyleSheet("background-color: #1e1e21;");
    leftPart->setStyleSheet("background-color: #2f2f30;");

    QGridLayout* rightPartMainLayout = new QGridLayout(this);
    QBoxLayout* controlAreaLayout = new QBoxLayout(QBoxLayout::RightToLeft, this);
    QVBoxLayout* informationArea = new QVBoxLayout(this);

    controlAreaLayout->addWidget(exitButton, 1);
    controlAreaLayout->addWidget(fullScreenButton, 1);
    controlAreaLayout->addWidget(collapseButton, 1);

    rightPartMainLayout->addLayout(controlAreaLayout, 0, 0, 1, 4);
    rightPartMainLayout->addLayout(informationArea, 1, 0, 3, 4);

    rightPartMainLayout->setSpacing(1);

    rightPart->setLayout(rightPartMainLayout);

    mainWindowLayout->addWidget(leftPart, 0, 0, 4, 1);

   
    mainWindowLayout->addWidget(rightPart, 0, 1, 4, 3);

}

void FileManagerClass::mousePressEvent(QMouseEvent *event)
{
    this->setStyleSheet("");
    if(event->button() == Qt::LeftButton) {
        this->offset = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
    }

}

void FileManagerClass::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton) {
        QPoint newPos = event->globalPosition().toPoint() - this->offset;
        std::cout << "Moving to: " << newPos.x() << ", " << newPos.y() << std::endl;

        this->move(newPos);
        this->update();

        event->accept();

        std::cout << "After move: " << this->pos().x() << ", " << this->pos().y() << std::endl;
    }
}

void FileManagerClass::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        this->unsetCursor();
    }
}
