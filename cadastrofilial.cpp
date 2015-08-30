#include "cadastrofilial.h"


QString CadastroFilial::getFilialEmpresa() const
{
    return filialEmpresa;
}

QString CadastroFilial::getFilialCodigo() const
{
    return filialCodigo;
}

QString CadastroFilial::getFilialTipo() const
{
    return filialTipo;
}

QString CadastroFilial::getFilialRazao() const
{
    return filialRazao;
}

QString CadastroFilial::getFilialNome() const
{
    return filialNome;
}

QString CadastroFilial::getFilialCgc() const
{
    return filialCgc;
}

QString CadastroFilial::getFilialInscricao() const
{
    return filialInscricao;
}
CadastroFilial::CadastroFilial(QString _filialEmpresa, QString _filialCodigo,
                               QString _filialTipo, QString _filialRazao,
                               QString _filialNome, QString _filialCgc, QString _filialInscricao) :
    filialEmpresa(_filialEmpresa), filialCodigo(_filialCodigo), filialTipo(_filialTipo),
    filialRazao(_filialRazao), filialNome(_filialNome), filialCgc(_filialCgc), filialInscricao(_filialInscricao)
{

}

