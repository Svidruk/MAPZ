#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->HTMLchecked->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CreateBot_clicked()
{
    PrototypeFactory *prototype_factory = new PrototypeFactory(ids);
    if(ui->DOCChecked->isChecked())
    {
         BotPrototype *bot = prototype_factory->CreateBot(Type::DOCBOT);
         BS = BotStorage::GetInstance();
         ui->BotSelector->insertItem(bot->getId(),"DOCBot id:" + QString::number(bot->getId()));
         BS->setBot(bot);
         delete prototype_factory;
    }
    else
    {
         BotPrototype *bot = prototype_factory->CreateBot(Type::HTMLBOT);
         BS = BotStorage::GetInstance();
         ui->BotSelector->insertItem(bot->getId(),"HTMLBot id:" + QString::number(bot->getId()));
         BS->setBot(bot);
         delete prototype_factory;
    }
}


void MainWindow::on_RunBot_clicked()
{
    if(BS->getSize()>0)
    {
        BotStorage::GetInstance()->getBotByIdx(ui->BotSelector->currentIndex())->CallInterface();
    }
}
