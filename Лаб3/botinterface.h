#ifndef BOTINTERFACE_H
#define BOTINTERFACE_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QSpinBox>


class AbstractBotInterface
{
public:
    //virtual ~AbstractBotInterface();
    virtual QPushButton *CreateButton() const = 0;
    virtual QLineEdit *CreateLineEdit() const = 0;
    virtual QSpinBox *CreateSpinBox() const = 0;
};


class DOCBotInterface: public AbstractBotInterface
{
public:
    QPushButton *CreateButton() const override;
    QLineEdit *CreateLineEdit() const override;
    QSpinBox *CreateSpinBox() const override;
};


class HTMLBotInterface: public AbstractBotInterface
{
public:
    QPushButton *CreateButton() const override;
    QLineEdit *CreateLineEdit() const override;
    QSpinBox *CreateSpinBox() const override;
};



class BotInterfaceFactory
{
public:
    AbstractBotInterface *CreateDOCBotInterface()const;
    AbstractBotInterface *CreateHTMLBotInterface()const;
};

namespace Ui {
class BotInterface;
}

class BotInterface : public QDialog
{
    Q_OBJECT

public:
    explicit BotInterface(AbstractBotInterface *BI, QWidget *parent = nullptr);
    ~BotInterface();
    void workWithData(QVector<QString>);

private:
    Ui::BotInterface *ui;
    QPushButton *PB;
    QLineEdit *LE;
    QSpinBox *SB;
};

#endif // BOTINTERFACE_H
