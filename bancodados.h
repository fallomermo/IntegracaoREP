#ifndef BANCODADOS_H
#define BANCODADOS_H

#include <QSql>
#include <QMap>
#include <QDate>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QMessageBox>

#include <cadastroempresa.h>
#include <cadastrofilial.h>
#include <cadastrocolaborador.h>

class BancoDados
{
    QString nomeConexao;

public:
    BancoDados();

    bool abrirConexao();
    void fecharConexao();
    bool isOpen();

    QString formatarData(QString _dataToFormat);

    QMap<int, CadastroEmpresa*> listarEmpresas();
    QMap<int, CadastroFilial*> listarFiliais(QString _empresa);
    QMap<int, CadastroColaborador*> listarColaboradores(QString _empresa, QString _filial, QString _dtIni, QString _dtFim);

private:
    QSqlDatabase db;

};

#endif // BANCODADOS_H
