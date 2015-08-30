#include "relacaofiliais.h"
#include "ui_relacaofiliais.h"

RelacaoFiliais::RelacaoFiliais(QMap<int,CadastroFilial*> &_lstFiliais, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RelacaoFiliais)
{
    ui->setupUi(this);

    connect(ui->campoPesquisa,SIGNAL(returnPressed()),this,SLOT(focusCampoPesquisaSelecionado()));
    connect(ui->tabelaPrincipal,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(retornaItemFilialSelecionado()));
    connect(ui->tabelaPrincipal,SIGNAL(clicked(QModelIndex)),this,SLOT(tipoAcaoBotaoSelecionarFechar()));
    connect(ui->tabelaPrincipal,SIGNAL(itemEntered(QTableWidgetItem*)),this,SLOT(retornaItemFilialSelecionado()));
    connect(ui->botaoFechar,SIGNAL(clicked(bool)),this,SLOT(acaoBotaoFechar()));

    QStringList tipoPesquisa;
    tipoPesquisa << "Código" << "Nome" << "CNPJ/CGC";
    ui->tipoPesquisa->addItems(tipoPesquisa);

    QTableWidgetItem * item;
    CadastroFilial * _objFilial;

    QStringList labelsColunas;
    labelsColunas << "Código" << "Filial" << "CNPJ/CGC";

    ui->tabelaPrincipal->setColumnCount(labelsColunas.count());
    ui->tabelaPrincipal->setHorizontalHeaderLabels(labelsColunas);
    int linha = 1;

    for (QMap<int,CadastroFilial*>::Iterator _it = _lstFiliais.begin(); _it != _lstFiliais.end(); ++_it) {
        ui->tabelaPrincipal->setRowCount(linha);
        _objFilial = _it.value();

        item = new QTableWidgetItem(QString("%0").arg(_objFilial->getFilialCodigo()));
        ui->tabelaPrincipal->setItem(linha-1,0,item);
        item = new QTableWidgetItem(QString("%0").arg(_objFilial->getFilialNome()));
        ui->tabelaPrincipal->setItem(linha-1,1,item);
        item = new QTableWidgetItem(QString("%0").arg(_objFilial->getFilialCgc()));
        ui->tabelaPrincipal->setItem(linha-1,2,item);
        linha++;
    }

    ui->tabelaPrincipal->resizeColumnsToContents();
}

RelacaoFiliais::~RelacaoFiliais()
{
    delete ui;
}

void RelacaoFiliais::retornaItemFilialSelecionado()
{
    int linha = ui->tabelaPrincipal->currentItem()->row();
    QTableWidgetItem * item = ui->tabelaPrincipal->item(linha,0);
    emit filialSelecionada(item->text());
    this->close();
}

void RelacaoFiliais::acaoBotaoFechar()
{
    if(ui->botaoFechar->text().contains("Selecionar")){
        retornaItemFilialSelecionado();
    } else {
        this->close();
    }
}

void RelacaoFiliais::alterarBotaoFechar()
{
    ui->botaoFechar->setText("Fechar");
}

void RelacaoFiliais::tipoAcaoBotaoSelecionarFechar()
{
    ui->botaoFechar->setText("Selecionar");
}

void RelacaoFiliais::focusCampoPesquisaSelecionado()
{
    ui->botaoFechar->setText("Selecionar");
    ui->tabelaPrincipal->setFocus();
    ui->tabelaPrincipal->selectRow(0);
}
