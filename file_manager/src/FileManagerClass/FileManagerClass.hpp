#ifndef FILEMANAGERCLASS
#define FILEMANAGERCLASS
#include <iostream>
#include <QtWidgets>

class FileManagerClass : public QWidget
{
QOBJECT_H
private:
    QLineEdit* searchingLine;
    QRect saveGeometry;
    QPoint offset;
public:
    FileManagerClass(QApplication*, QWidget* = nullptr);
    ~FileManagerClass() = default;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
public slots:
    void fullScreenSlot();
};


#endif //FILEMANAGERCLASS
