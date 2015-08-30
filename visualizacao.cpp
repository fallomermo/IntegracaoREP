#include "visualizacao.h"
#include "ui_visualizacao.h"

Visualizacao::Visualizacao(QMap<int, CadastroColaborador*> _integrados, QString _empresaSelecionada, QWidget *parent) :
    QWidget(parent), empresaSelecionada(_empresaSelecionada),
    ui(new Ui::Visualizacao)
{
    ui->setupUi(this);
    ui->campoEmpresaProcessada->setText(empresaSelecionada);
    connect(ui->botaoFechar,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->botaoFechar,SIGNAL(pressed()),this,SLOT(close()));

    QTableWidgetItem * item;
    CadastroColaborador * _objCadastro;

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

    ui->tabelaVisualizacao->setColumnCount(colunasTabela.count());
    ui->tabelaVisualizacao->setHorizontalHeaderLabels(colunasTabela);
    int linha = 1;
    for (QMap<int, CadastroColaborador*>::iterator _it = _integrados.begin();_it != _integrados.end(); ++_it) {
        ui->tabelaVisualizacao->setRowCount(linha);
        _objCadastro = _it.value();

        for (int coluna = 0; coluna < colunasTabela.size(); ++coluna) {
            item = new QTableWidgetItem(QString("%0").arg(retornaItemMapColaborador(_objCadastro,coluna)));
            ui->tabelaVisualizacao->setItem(linha-1,coluna,item);
        }
        linha++;
    }

    ui->tabelaVisualizacao->resizeColumnsToContents();
}

Visualizacao::~Visualizacao()
{
    delete ui;
}

QString Visualizacao::fomatarData(QString _data)
{
    QDate _dataEdit = QDate::fromString(_data);
    return QString(_dataEdit.toString("DD/MM/YYYY"));
}

QString Visualizacao::retornaItemMapColaborador(CadastroColaborador *_objCadastro,int _coluna)
{
    switch (_coluna) {
    case 0: return _objCadastro->getColEmpresa(); break;
    case 1: return _objCadastro->getColFilial(); break;
    case 2: return _objCadastro->getColMatricula(); break;
    case 3: return _objCadastro->getColNome(); break;
    case 4: return _objCadastro->getColCpf(); break;
    case 5: return _objCadastro->getColPis(); break;
    case 6: return _objCadastro->getColDataNascimento(); break;
    case 7: return _objCadastro->getColDataAdmissao(); break;
    case 8: return _objCadastro->getColSexo(); break;
    case 9: return _objCadastro->getColSetor(); break;
    case 10: return _objCadastro->getColLocalizacaoREP(); break;
    case 11: return _objCadastro->getColCracha(); break;
    case 12: return _objCadastro->getColTipoPonto(); break;
    case 13: return _objCadastro->getColSituacao(); break;
    case 14: return _objCadastro->getColCargo(); break;
    default: return ""; break;
    }
}
