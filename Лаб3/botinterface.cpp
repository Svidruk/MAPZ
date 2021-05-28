#include "botinterface.h"
#include "ui_botinterface.h"

BotInterface::BotInterface(AbstractBotInterface *BI,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BotInterface)
{
    ui->setupUi(this);
    ui->gridLayout->addWidget(BI->CreateButton());
    ui->gridLayout->addWidget(BI->CreateLineEdit());
    ui->gridLayout->addWidget(BI->CreateSpinBox());
}

BotInterface::~BotInterface()
{
    delete ui;
}

void BotInterface::workWithData(QVector<QString> VS)
{
    if(!VS.isEmpty())
    ui->textEdit->setText(VS.first());
}

QPushButton *DOCBotInterface::CreateButton() const {
    QPushButton *PB = new QPushButton();
    PB->setText("Start DOCBot");
    PB->setStyleSheet("QPushButton {color: red;}");
    return PB;
}

QLineEdit *DOCBotInterface::CreateLineEdit() const{
    QLineEdit *LE = new QLineEdit();
    LE->setStyleSheet("QLineEdit {color: red;}");
    return LE;
}

QSpinBox *DOCBotInterface::CreateSpinBox() const{
    QSpinBox *SB = new QSpinBox();
    SB->setStyleSheet("QSpinBox {color: red;}");
    return SB;
}

QPushButton *HTMLBotInterface::CreateButton() const{
    QPushButton *PB = new QPushButton();
    PB->setText("Start HTMLBot");
    PB->setStyleSheet("QPushButton {color: blue;}");
    return PB;
}

QLineEdit *HTMLBotInterface::CreateLineEdit() const{
    QLineEdit *LE = new QLineEdit();
    LE->setStyleSheet("QLineEdit {color: blue;}");
    return LE;
}

QSpinBox *HTMLBotInterface::CreateSpinBox() const{
    QSpinBox *SB = new QSpinBox();
    SB->setStyleSheet("QSpinBox {color: blue;}");
    return SB;
}

AbstractBotInterface *BotInterfaceFactory::CreateDOCBotInterface() const {
    return new DOCBotInterface();
}

AbstractBotInterface *BotInterfaceFactory::CreateHTMLBotInterface() const {
    return new HTMLBotInterface();
}
