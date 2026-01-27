#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QIntValidator>
#include <QColorDialog>
#include <QMessageBox>

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    QColor getColor() const;
    
    static bool getRectangleParameters(QWidget *parent, int &x, int &y, 
                                       int &width, int &height, QColor &color);

private slots:
    void onColorButtonClicked();
    void validateInput();
    void accept() override;

private:
    QLineEdit *m_xEdit;
    QLineEdit *m_yEdit;
    QLineEdit *m_widthEdit;
    QLineEdit *m_heightEdit;
    QPushButton *m_colorButton;
    QColor m_selectedColor;
    
    void setupUI();
    bool validateField(QLineEdit *edit, const QString &fieldName, int &value);
};

#endif // INPUTDIALOG_H