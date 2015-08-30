#ifndef RELACAOFILIAIS_H
#define RELACAOFILIAIS_H

#include <QMap>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <desktophome.h>
#include <cadastrofilial.h>

namespace Ui {
class RelacaoFiliais;
}

class RelacaoFiliais : public QWidget
{
    Q_OBJECT

public:
    explicit RelacaoFiliais(QMap<int,CadastroFilial*> &_lstFiliais, QWidget *parent = 0);
    ~RelacaoFiliais();

signals:
    void filialSelecionada(QString);

private slots:
    void retornaItemFilialSelecionado();
    void acaoBotaoFechar();
    void alterarBotaoFechar();
    void tipoAcaoBotaoSelecionarFechar();

    void focusCampoPesquisaSelecionado();

private:
    Ui::RelacaoFiliais *ui;
};

#endif // RELACAOFILIAIS_H
