#ifndef CADASTROCOLABORADOR_H
#define CADASTROCOLABORADOR_H

#include <QString>

class CadastroColaborador
{
    QString colEmpresa;
    QString colFilial;
    QString colMatricula;
    QString colNome;
    QString colCpf;
    QString colPis;
    QString colDataNascimento;
    QString colDataAdmissao;
    QString colSexo;
    QString colSetor;
    QString colLocalizacaoREP;
    QString colCracha;
    QString colTipoPonto;
    QString colSituacao;
    QString colCargo;

public:
    CadastroColaborador(QString _colEmpresa,
                        QString _colFilial,
                        QString _colMatricula,
                        QString _colNome,
                        QString _colCpf,
                        QString _colPis,
                        QString _colDataNascimento,
                        QString _colDataAdmissao,
                        QString _colSexo,
                        QString _colSetor,
                        QString _colLocalizacaoREP,
                        QString _colCracha,
                        QString _colTipoPonto,
                        QString _colSituacao,
                        QString _colCargo);

    QString getColEmpresa() const;
    QString getColFilial() const;
    QString getColMatricula() const;
    QString getColNome() const;
    QString getColCpf() const;
    QString getColPis() const;
    QString getColDataNascimento() const;
    QString getColDataAdmissao() const;
    QString getColSexo() const;
    QString getColSetor() const;
    QString getColLocalizacaoREP() const;
    QString getColCracha() const;
    QString getColTipoPonto() const;
    QString getColSituacao() const;
    QString getColCargo() const;
};

#endif // CADASTROCOLABORADOR_H
