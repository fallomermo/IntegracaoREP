#include "desktophome.h"
#include "ui_desktophome.h"


QMap<int, CadastroColaborador *> DesktopHome::getColaboradoresIntegrados() const
{
    return colaboradoresIntegrados;
}

void DesktopHome::setColaboradoresIntegrados(const QMap<int, CadastroColaborador *> &_integrados)
{
    ui->barraProgresso->setMaximum(_integrados.count());
    int totalRegitros = _integrados.count();

    for (int item = 0;item <= totalRegitros; ++item) {ui->barraProgresso->setValue(item);}

    ui->barraProgresso->setMaximum(100);
    ui->barraProgresso->setValue(100);
    ui->barraProgresso->repaint();

    if(totalRegitros != 0 || totalRegitros > 0) {
        colaboradoresIntegrados = _integrados;
        QMessageBox::information(this,
                                 QString("Integração REP"),
                                 QString("Colaboradores Integrados com Sucesso!\n%0 Registros Processados.")
                                 .arg(_integrados.count()),"OK");
        preVisualizarColaboradores();
    } else {
        colaboradoresIntegrados.clear();
        QMessageBox::information(this,
                                 QString("Integração REP"),
                                 QString("Nenhum colaborador processado!"),"OK");
    }
}

QMap<int, CadastroColaborador *> DesktopHome::getColaboradoresParaIntegrar() const
{
    return colaboradoresParaIntegrar;
}

void DesktopHome::setColaboradoresParaIntegrar(const QMap<int, CadastroColaborador *> &_aIntegrar)
{
    colaboradoresParaIntegrar = _aIntegrar;
}
DesktopHome::DesktopHome(QString _usuarioLogado, QWidget *parent) :
    QWidget(parent), usuarioLogado(_usuarioLogado),
    ui(new Ui::DesktopHome)
{
    ui->setupUi(this);
    carregarParametros();
    iniciaSnaisComSlots();
    aplicarDataCorrente();

    ui->comboBoxEmpresas->addItems(QStringList(usuarioLogado));
}

DesktopHome::~DesktopHome()
{
    delete ui;
}

void DesktopHome::fecharSistema()
{
    int rQuest = QMessageBox::question(this, QString("Encerrar aplicação"), QString("Deseja realmente sair?"),"Sim", "Não");
    if(rQuest == 0) {
        emit fecharHome();
        qApp->exit(0);
    }
}

void DesktopHome::iniciaSnaisComSlots()
{
    connect(ui->botaoSair,SIGNAL(clicked(bool)),this,SLOT(fecharSistema()));
    connect(ui->botaoSair,SIGNAL(pressed()),this,SLOT(fecharSistema()));
    connect(ui->botaoAplicarData,SIGNAL(clicked(bool)),this,SLOT(aplicarDataCorrente()));

    connect(ui->comboBoxEmpresas,SIGNAL(currentIndexChanged(int)),this,SLOT(focusCampoSelecionarEmpresa()));
    connect(ui->dataInicial,SIGNAL(editingFinished()),this,SLOT(focusCampoDataInicialPressionado()));
    connect(ui->dataFinal,SIGNAL(editingFinished()),this,SLOT(focusCampoDataFinalPressionado()));
    connect(ui->campoCodigoFilial,SIGNAL(returnPressed()),this,SLOT(focusCampoFilialPressionado()));
    connect(ui->campoCodigoColaborador,SIGNAL(returnPressed()),this,SLOT(focusCampoColaboradorPressionado()));
    connect(ui->botaoVisulizar,SIGNAL(clicked(bool)),this,SLOT(preVisualizarColaboradores()));

    connect(ui->botaoPesquisaFilial,SIGNAL(clicked(bool)),this,SLOT(listaFiliaisCadastradas()));
    connect(ui->botaoPesquisaColaborador,SIGNAL(clicked(bool)),this,SLOT(listaColaboradoresPonto()));
    connect(ui->botaoCancelar,SIGNAL(clicked(bool)),this,SLOT(ativarCamposEdicao()));

    connect(ui->botaoIntegrar,SIGNAL(clicked(bool)),this,SLOT(acaoIntegrar()));
}

void DesktopHome::aplicarDataCorrente()
{
    ui->dataInicial->setDate(QDate::currentDate());
    ui->dataFinal->setDate(QDate::currentDate());
}

void DesktopHome::carregarParametros()
{
    ui->comboBoxEmpresas->addItem("Selecione uma empresa: ");
    listaEmpresasCadastradas();
}

void DesktopHome::focusAutomatico()
{
    //
}

void DesktopHome::focusCampoSelecionarEmpresa()
{
    ui->dataInicial->setFocus();
}

void DesktopHome::focusCampoDataInicialPressionado()
{
    ui->dataFinal->setFocus();
}

void DesktopHome::focusCampoDataFinalPressionado()
{
    ui->campoCodigoFilial->setFocus();
}

void DesktopHome::focusCampoFilialPressionado()
{
    ui->campoCodigoColaborador->setFocus();
}

void DesktopHome::focusCampoColaboradorPressionado()
{
    ui->botaoIntegrar->setFocus();
}

void DesktopHome::ativarCamposEdicao()
{
    ui->dataInicial->isActiveWindow();
}

void DesktopHome::testeBancoDados()
{
    BancoDados * db = new BancoDados;
    db->abrirConexao();
}

void DesktopHome::testarMetodos()
{
    qDebug() << "Indice Combo " << ui->comboBoxEmpresas->currentIndex();
}

void DesktopHome::listaEmpresasCadastradas()
{
    QStringList lstEmpresas;

    QMap<int,CadastroEmpresa*> empresas = db->listarEmpresas();
    QMap<int,CadastroEmpresa*>::Iterator it = empresas.begin();

    for (;it != empresas.end(); ++it) {
        CadastroEmpresa *_cadEmp = it.value();
        lstEmpresas.append(QString("%0 - %1").arg(_cadEmp->getEmpresaCodigo()).arg(_cadEmp->getEmpresaNome()));
    }
    ui->comboBoxEmpresas->addItems(lstEmpresas);
}

void DesktopHome::listaFiliaisCadastradas()
{
    if(ui->comboBoxEmpresas->currentIndex() == 0){
        QMessageBox::critical(this, QString("Listar Filais"), QString("Nenhuma empresa selecionada!"),"OK");
        ui->comboBoxEmpresas->setFocus();
    } else {
        QMap<int,CadastroFilial*> mapFiliais;
        mapFiliais = db->listarFiliais(QString("100%0").arg(ui->comboBoxEmpresas->currentIndex()));
        RelacaoFiliais * janelaFilial = new RelacaoFiliais(mapFiliais,this);
        connect(janelaFilial,SIGNAL(filialSelecionada(QString)),this,SLOT(retornaCodigoFilial(QString)));
        janelaFilial->setWindowFlags(Qt::Window);
        janelaFilial->setWindowModality(Qt::ApplicationModal);
        QRect area = this->geometry();
        QPoint centralizar = area.center();
        janelaFilial->move(centralizar.x()-janelaFilial->width()*0.5,centralizar.y()-janelaFilial->height()*0.5);
        janelaFilial->show();
    }
}

void DesktopHome::listaColaboradoresPonto()
{
    if(ui->comboBoxEmpresas->currentIndex() == 0){
        QMessageBox::critical(this, QString("Listar Colaboradores"), QString("Nenhuma empresa selecionada!"),"OK");
        ui->comboBoxEmpresas->setFocus();
    } else {
        QMap<int,CadastroColaborador*> mapColaboradores;
        mapColaboradores = db->listarColaboradores(QString("100%0").arg(ui->comboBoxEmpresas->currentIndex()),
                                                   ui->campoCodigoFilial->text(),
                                                   ui->dataInicial->date().toString(Qt::ISODate),
                                                   ui->dataFinal->date().toString(Qt::ISODate));
        RelacaoColaboradores * jColaborador = new RelacaoColaboradores(mapColaboradores,this);

        connect(jColaborador,SIGNAL(colaboradorSelecionado(QString)),
                this,SLOT(retornaCodigoColaborador(QString)));
        connect(jColaborador,SIGNAL(listaColaboradores(QMap<int,CadastroColaborador*>)),
                this,SLOT(setListaColaboradores(QMap<int,CadastroColaborador*>)));

        jColaborador->setWindowFlags(Qt::Window);
        jColaborador->setWindowModality(Qt::ApplicationModal);
        QRect area = this->geometry();
        QPoint centralizar = area.center();
        jColaborador->move(centralizar.x()-jColaborador->width()*0.5,centralizar.y()-jColaborador->height()*0.5);
        jColaborador->show();
    }
}

void DesktopHome::setListaColaboradores(QMap<int, CadastroColaborador *> _lista)
{
    setColaboradoresParaIntegrar(_lista);
}

void DesktopHome::retornaCodigoFilial(QString _codfil)
{
    ui->campoCodigoFilial->clear();
    ui->campoCodigoFilial->setFocus();
    ui->campoCodigoFilial->setText(_codfil);
    ui->campoCodigoFilial->selectAll();
}

void DesktopHome::retornaCodigoColaborador(QString _matricula)
{
    ui->campoCodigoColaborador->clear();
    ui->campoCodigoColaborador->setFocus();
    ui->campoCodigoColaborador->setText(_matricula);
    ui->campoCodigoColaborador->selectAll();
}

void DesktopHome::preVisualizarColaboradores()
{
    if(ui->comboBoxEmpresas->currentIndex() != 0){
        visualizar = new Visualizacao(colaboradoresIntegrados,ui->comboBoxEmpresas->currentText(),this);
        visualizar->setWindowFlags(Qt::Window);
        visualizar->setWindowModality(Qt::ApplicationModal);
        visualizar->show();
    } else {
        QMessageBox::critical(this, QString("Visualizar Colaboradores"), QString("Nenhuma empresa selecionada!"),"OK");
    }
}

void DesktopHome::acaoIntegrar()
{
    if(ui->comboBoxEmpresas->currentIndex() == 0){
        QMessageBox::critical(this, QString("Listar Filais"), QString("Nenhuma empresa selecionada!"),"OK");
        ui->comboBoxEmpresas->setFocus();
    } else {
        if(getColaboradoresIntegrados().count() != 0)
            integrarColaboradoresREP(getColaboradoresParaIntegrar(),ui->campoCodigoColaborador->text());
        setColaboradoresParaIntegrar(db->listarColaboradores(QString("100%0").arg(ui->comboBoxEmpresas->currentIndex()),
                                                             ui->campoCodigoFilial->text(),
                                                             ui->dataInicial->date().toString(Qt::ISODate),
                                                             ui->dataFinal->date().toString(Qt::ISODate)));
        integrarColaboradoresREP(colaboradoresParaIntegrar,ui->campoCodigoColaborador->text());
    }
}

void DesktopHome::integrarColaboradoresREP(QMap<int, CadastroColaborador *> _integracao, QString _matriculas)
{
    if(_matriculas.isEmpty() || _matriculas.isNull()){
        setColaboradoresIntegrados(_integracao);
    } else {
        CadastroColaborador * cadastro;
        bool _processar = true;
        int _indice = 0;
        QMap<int, CadastroColaborador *> _integrar;
        for (QMap<int, CadastroColaborador *>::iterator _it = _integracao.begin();
             _it != _integracao.end() || _processar == true; ++_it) {
            _indice++;
            cadastro = _it.value();
            if (cadastro->getColMatricula() == _matriculas) {
                _integrar.insert(_indice,cadastro);
                _processar = false;
            }
        }

        setColaboradoresIntegrados(_integrar);

    }
}

void DesktopHome::closeEvent(QCloseEvent * evClose)
{
    evClose->ignore();
    fecharSistema();
}

void DesktopHome::keyPressEvent(QKeyEvent * evKey)
{
    if(evKey->key() == Qt::Key_Escape){
        fecharSistema();
    }
}

