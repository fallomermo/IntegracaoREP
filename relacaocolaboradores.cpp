#include "relacaocolaboradores.h"
#include "ui_relacaocolaboradores.h"

RelacaoColaboradores::RelacaoColaboradores(QMap<int, CadastroColaborador *> _colaboradores, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RelacaoColaboradores)
{
    ui->setupUi(this);

    //connect(ui->campoPesquia,SIGNAL(returnPressed()),this,SLOT(focusCampoPesquisaSelecionado()));
    connect(ui->tabelaPrincipal,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(retornaItemColaboradorSelecionado()));
    //connect(ui->tabelaPrincipal,SIGNAL(clicked(QModelIndex)),this,SLOT(tipoAcaoBotaoSelecionarFechar()));
    connect(ui->tabelaPrincipal,SIGNAL(itemEntered(QTableWidgetItem*)),this,SLOT(retornaItemColaboradorSelecionado()));
    //connect(ui->botaoPrincipal,SIGNAL(clicked(bool)),this,SLOT(acaoBotaoFechar()));

    QStringList colunasTabela;
    colunasTabela << "Empresa"
                  << "Filial"
                  << "Matricula"
                  << "Nome"
                  << "Cpf"
                  << "Pis"
                  << "Data Nascimento"
                  << "Data Admissão"
                  << "Sexo"
                  << "Setor"
                  << "Localização REP"
                  << "Crachá"
                  << "Tipo Ponto"
                  << "Situacão"
                  << "Cargo";

    ui->tipoPesquisa->addItems(colunasTabela);
    ui->tabelaPrincipal->setColumnCount(colunasTabela.count());
    ui->tabelaPrincipal->setHorizontalHeaderLabels(colunasTabela);

    QMap<int, CadastroColaborador *> _lista = _colaboradores;
    QTableWidgetItem * item;
    CadastroColaborador * _cadCol;
    int linha = 1;

    for (QMap<int, CadastroColaborador *>::iterator _it = _lista.begin();
         _it != _lista.end(); ++_it) {
        ui->tabelaPrincipal->setRowCount(linha);

        _cadCol = _it.value();
        for (int coluna = 0; coluna < colunasTabela.size(); ++coluna) {
            item = new QTableWidgetItem(QString("%0").arg(retornaInfoColaborador(coluna,_cadCol)));
            ui->tabelaPrincipal->setItem(linha-1,coluna,item);
        }
        linha++;
    }
    ui->tabelaPrincipal->resizeColumnsToContents();
}

RelacaoColaboradores::~RelacaoColaboradores()
{
    delete ui;
}

void RelacaoColaboradores::retornaItemColaboradorSelecionado()
{
    int linha = ui->tabelaPrincipal->currentItem()->row();
    QTableWidgetItem * item = ui->tabelaPrincipal->item(linha,2);
    emit colaboradorSelecionado(item->text());
    this->close();
}

QString RelacaoColaboradores::retornaInfoColaborador(int _coluna, CadastroColaborador * _cadastro)
{
    switch (_coluna) {
    case 0: return _cadastro->getColEmpresa(); break;
    case 1: return _cadastro->getColFilial(); break;
    case 2: return _cadastro->getColMatricula(); break;
    case 3: return _cadastro->getColNome(); break;
    case 4: return _cadastro->getColCpf(); break;
    case 5: return _cadastro->getColPis(); break;
    case 6: return _cadastro->getColDataNascimento(); break;
    case 7: return _cadastro->getColDataAdmissao(); break;
    case 8: return _cadastro->getColSexo(); break;
    case 9: return _cadastro->getColSetor(); break;
    case 10: return _cadastro->getColLocalizacaoREP(); break;
    case 11: return _cadastro->getColCracha(); break;
    case 12: return _cadastro->getColTipoPonto(); break;
    case 13: return _cadastro->getColSituacao(); break;
    case 14: return _cadastro->getColCargo(); break;
    default: return ""; break;
        break;
    }
}
