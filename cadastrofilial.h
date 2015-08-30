#ifndef CADASTROFILIAL_H
#define CADASTROFILIAL_H

#include <QString>

class CadastroFilial
{
    QString filialEmpresa;
    QString filialCodigo;
    QString filialTipo;
    QString filialRazao;
    QString filialNome;
    QString filialCgc;
    QString filialInscricao;

public:
    CadastroFilial(QString _filialEmpresa,QString _filialCodigo,
                   QString _filialTipo, QString _filialRazao,
                   QString _filialNome, QString _filialCgc, QString _filialInscricao);
    QString getFilialEmpresa() const;
    QString getFilialCodigo() const;
    QString getFilialTipo() const;
    QString getFilialRazao() const;
    QString getFilialNome() const;
    QString getFilialCgc() const;
    QString getFilialInscricao() const;
};

#endif // CADASTROFILIAL_H
