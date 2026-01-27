#include "inputdialog.h"

InputDialog::InputDialog(QWidget *parent)
    : QDialog(parent), m_selectedColor(Qt::blue)
{
    setupUI();
    setWindowTitle("Enter Rectangle Parameters");
    setModal(true);
    resize(400, 250);
}

void InputDialog::setupUI()
{
    QFormLayout *layout = new QFormLayout(this);
    
    m_xEdit = new QLineEdit(this);
    m_xEdit->setValidator(new QIntValidator(-1000, 1000, this));
    m_xEdit->setText("100");
    
    m_yEdit = new QLineEdit(this);
    m_yEdit->setValidator(new QIntValidator(-1000, 1000, this));
    m_yEdit->setText("100");
    
    m_widthEdit = new QLineEdit(this);
    m_widthEdit->setValidator(new QIntValidator(10, 500, this));
    m_widthEdit->setText("200");
    
    m_heightEdit = new QLineEdit(this);
    m_heightEdit->setValidator(new QIntValidator(10, 500, this));
    m_heightEdit->setText("100");
    
    m_colorButton = new QPushButton("Choose Color", this);
    m_colorButton->setStyleSheet(QString("background-color: %1;").arg(m_selectedColor.name()));
    connect(m_colorButton, &QPushButton::clicked, this, &InputDialog::onColorButtonClicked);
    
    layout->addRow("X coordinate:", m_xEdit);
    layout->addRow("Y coordinate:", m_yEdit);
    layout->addRow("Width:", m_widthEdit);
    layout->addRow("Height:", m_heightEdit);
    layout->addRow("Color:", m_colorButton);
    
    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addRow(buttonLayout);
    
    connect(okButton, &QPushButton::clicked, this, &InputDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &InputDialog::reject);
    connect(m_xEdit, &QLineEdit::textChanged, this, &InputDialog::validateInput);
    connect(m_yEdit, &QLineEdit::textChanged, this, &InputDialog::validateInput);
    connect(m_widthEdit, &QLineEdit::textChanged, this, &InputDialog::validateInput);
    connect(m_heightEdit, &QLineEdit::textChanged, this, &InputDialog::validateInput);
    
    validateInput();
}

void InputDialog::onColorButtonClicked()
{
    QColor color = QColorDialog::getColor(m_selectedColor, this, "Choose Color");
    if (color.isValid()) {
        m_selectedColor = color;
        m_colorButton->setStyleSheet(QString("background-color: %1;").arg(color.name()));
    }
}

void InputDialog::validateInput()
{
    bool xValid = m_xEdit->hasAcceptableInput();
    bool yValid = m_yEdit->hasAcceptableInput();
    bool widthValid = m_widthEdit->hasAcceptableInput();
    bool heightValid = m_heightEdit->hasAcceptableInput();
    
    QString errorStyle = "background-color: #ffcccc;";
    QString normalStyle = "";
    
    m_xEdit->setStyleSheet(xValid ? normalStyle : errorStyle);
    m_yEdit->setStyleSheet(yValid ? normalStyle : errorStyle);
    m_widthEdit->setStyleSheet(widthValid ? normalStyle : errorStyle);
    m_heightEdit->setStyleSheet(heightValid ? normalStyle : errorStyle);
}

void InputDialog::accept()
{
    int x, y, width, height;
    
    if (!validateField(m_xEdit, "X coordinate", x)) return;
    if (!validateField(m_yEdit, "Y coordinate", y)) return;
    if (!validateField(m_widthEdit, "Width", width)) return;
    if (!validateField(m_heightEdit, "Height", height)) return;
    
    if (width <= 0 || height <= 0) {
        QMessageBox::warning(this, "Error", "Width and height must be positive!");
        return;
    }
    
    QDialog::accept();
}

bool InputDialog::validateField(QLineEdit *edit, const QString &fieldName, int &value)
{
    if (!edit->hasAcceptableInput()) {
        QMessageBox::warning(this, "Error", 
                           QString("Field '%1' contains invalid value!").arg(fieldName));
        edit->setFocus();
        return false;
    }
    
    bool ok;
    value = edit->text().toInt(&ok);
    return ok;
}

int InputDialog::getX() const { return m_xEdit->text().toInt(); }
int InputDialog::getY() const { return m_yEdit->text().toInt(); }
int InputDialog::getWidth() const { return m_widthEdit->text().toInt(); }
int InputDialog::getHeight() const { return m_heightEdit->text().toInt(); }
QColor InputDialog::getColor() const { return m_selectedColor; }

bool InputDialog::getRectangleParameters(QWidget *parent, int &x, int &y, 
                                         int &width, int &height, QColor &color)
{
    InputDialog dialog(parent);
    if (dialog.exec() == QDialog::Accepted) {
        x = dialog.getX();
        y = dialog.getY();
        width = dialog.getWidth();
        height = dialog.getHeight();
        color = dialog.getColor();
        return true;
    }
    return false;
}