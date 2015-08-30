#ifndef CADASTROEMPRESA_H
#define CADASTROEMPRESA_H

#include <QString>

class CadastroEmpresa
{
    QString empresaCodigo;
    QString empresaRazao;
    QString empresaNome;
public:
    CadastroEmpresa(QString _empresaCodigo, QString _empresaRazao, QString _empresaNome);

    QString getEmpresaCodigo() const;
    QString getEmpresaRazao() const;
    QString getEmpresaNome() const;
};

#endif // CADASTROEMPRESA_H
