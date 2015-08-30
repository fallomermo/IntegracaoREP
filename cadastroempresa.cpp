#include "cadastroempresa.h"


QString CadastroEmpresa::getEmpresaCodigo() const
{
    return empresaCodigo;
}

QString CadastroEmpresa::getEmpresaRazao() const
{
    return empresaRazao;
}

QString CadastroEmpresa::getEmpresaNome() const
{
    return empresaNome;
}
CadastroEmpresa::CadastroEmpresa(QString _empresaCodigo,QString _empresaRazao,QString _empresaNome) :
    empresaCodigo(_empresaCodigo), empresaRazao(_empresaRazao), empresaNome(_empresaNome)
{}

