#ifndef RELACAOCOLABORADORES_H
#define RELACAOCOLABORADORES_H

#include <QWidget>
#include <QDebug>

#include <cadastrocolaborador.h>

namespace Ui {
class RelacaoColaboradores;
}

class RelacaoColaboradores : public QWidget
{
    Q_OBJECT

public:
    explicit RelacaoColaboradores(QMap<int, CadastroColaborador*> _colaboradores,QWidget *parent = 0);
    ~RelacaoColaboradores();

signals:
    void colaboradorSelecionado(QString);
    void listaColaboradores(QMap<int, CadastroColaborador *>);

private slots:
    void retornaItemColaboradorSelecionado();
    QString retornaInfoColaborador(int _coluna, CadastroColaborador *_cadastro);


private:
    Ui::RelacaoColaboradores *ui;
};

#endif // RELACAOCOLABORADORES_H
