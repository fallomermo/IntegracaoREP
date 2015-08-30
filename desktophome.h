#ifndef DESKTOPHOME_H
#define DESKTOPHOME_H

#include <QMap>
#include <QDebug>
#include <QWidget>
#include <QKeyEvent>
#include <QMessageBox>

#include "bancodados.h"
#include "relacaofiliais.h"
#include "relacaocolaboradores.h"
#include "visualizacao.h"
#include "cadastroempresa.h"
#include "cadastrofilial.h"


namespace Ui {
class DesktopHome;
}

class DesktopHome : public QWidget
{
    Q_OBJECT
    QString usuarioLogado;
    QMap<int, CadastroColaborador*> colaboradoresParaIntegrar;
    QMap<int, CadastroColaborador*> colaboradoresIntegrados;


public:
    explicit DesktopHome(QString _usuarioLogado,QWidget *parent = 0);
    ~DesktopHome();

    QMap<int, CadastroColaborador *> getColaboradoresIntegrados() const;
    void setColaboradoresIntegrados(const QMap<int, CadastroColaborador *> &_integrados);

    QMap<int, CadastroColaborador *> getColaboradoresParaIntegrar() const;
    void setColaboradoresParaIntegrar(const QMap<int, CadastroColaborador *> &_aIntegrar);

signals:
    void fecharHome();signals:
    void focusAtivado(bool hasFocus);

private slots:
    void fecharSistema();
    void iniciaSnaisComSlots();
    void aplicarDataCorrente();
    void carregarParametros();

    void focusAutomatico();
    void focusCampoSelecionarEmpresa();
    void focusCampoDataInicialPressionado();
    void focusCampoDataFinalPressionado();
    void focusCampoFilialPressionado();
    void focusCampoColaboradorPressionado();

    void ativarCamposEdicao();
    void testeBancoDados();
    void testarMetodos();

    void listaEmpresasCadastradas();
    void listaFiliaisCadastradas();
    void listaColaboradoresPonto();
    void setListaColaboradores(QMap<int, CadastroColaborador *>);
    void retornaCodigoFilial(QString);
    void retornaCodigoColaborador(QString);
    void preVisualizarColaboradores();

    void acaoIntegrar();
    void integrarColaboradoresREP(QMap<int, CadastroColaborador*> _integracao, QString _matriculas);

protected:
    virtual void closeEvent(QCloseEvent *evClose);
    virtual void keyPressEvent(QKeyEvent * evKey);

private:
    Ui::DesktopHome *ui;
    BancoDados * db;
    Visualizacao * visualizar;
};

#endif // DESKTOPHOME_H
