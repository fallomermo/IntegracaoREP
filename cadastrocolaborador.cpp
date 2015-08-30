#include "cadastrocolaborador.h"


QString CadastroColaborador::getColEmpresa() const {return colEmpresa;}
QString CadastroColaborador::getColFilial() const {return colFilial;}
QString CadastroColaborador::getColMatricula() const {return colMatricula;}
QString CadastroColaborador::getColNome() const {return colNome;}
QString CadastroColaborador::getColCpf() const {return colCpf;}
QString CadastroColaborador::getColPis() const {return colPis;}
QString CadastroColaborador::getColDataNascimento() const {return colDataNascimento;}
QString CadastroColaborador::getColDataAdmissao() const {return colDataAdmissao;}
QString CadastroColaborador::getColSexo() const {return colSexo;}
QString CadastroColaborador::getColSetor() const {return colSetor;}
QString CadastroColaborador::getColLocalizacaoREP() const {return colLocalizacaoREP;}
QString CadastroColaborador::getColCracha() const {return colCracha;}
QString CadastroColaborador::getColTipoPonto() const {return colTipoPonto;}
QString CadastroColaborador::getColSituacao() const {return colSituacao;}
QString CadastroColaborador::getColCargo() const {return colCargo;}

CadastroColaborador::CadastroColaborador(QString _colEmpresa,
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
                                         QString _colCargo) :
    colEmpresa(_colEmpresa),
    colFilial(_colFilial),
    colMatricula(_colMatricula),
    colNome(_colNome),
    colCpf(_colCpf),
    colPis(_colPis),
    colDataNascimento(_colDataNascimento),
    colDataAdmissao(_colDataAdmissao),
    colSexo(_colSexo),
    colSetor(_colSetor),
    colLocalizacaoREP(_colLocalizacaoREP),
    colCracha(_colCracha),
    colTipoPonto(_colTipoPonto),
    colSituacao(_colSituacao),
    colCargo(_colCargo){}

