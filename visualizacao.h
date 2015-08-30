#ifndef VISUALIZACAO_H
#define VISUALIZACAO_H

#include <QDate>
#include <QWidget>
#include <QTableWidgetItem>

#include "cadastrocolaborador.h"

namespace Ui {
class Visualizacao;
}

class Visualizacao : public QWidget
{
    Q_OBJECT
    QString empresaSelecionada;

public:
    explicit Visualizacao(QMap<int, CadastroColaborador *> _integrados, QString _empresaSelecionada, QWidget *parent = 0);
    ~Visualizacao();

    QString fomatarData(QString _data);


private slots:
    QString retornaItemMapColaborador(CadastroColaborador *_objCadastro, int _coluna);

private:
    Ui::Visualizacao *ui;
    CadastroColaborador * _cadastro;
};

#endif // VISUALIZACAO_H
