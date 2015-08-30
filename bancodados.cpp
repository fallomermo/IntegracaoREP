#include "bancodados.h"

BancoDados::BancoDados()
{
    nomeConexao = "DRIVER={FreeTDS};"
                  "Server=192.168.6.4;"
                  "Database=vetorh_homol;"
                  "Uid=ti;"
                  "Port=1433;"
                  "Pwd=magnum9000;"
                  "WSID=";
}

bool BancoDados::abrirConexao()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(nomeConexao);

    if (!db.open()) {
        QMessageBox::critical(0, QString("Conexão Base de Dados"),
                              QString("Não foi possível iniciar conexão com o Banco %0!\n%1")
                              .arg(db.databaseName())
                              .arg(db.lastError().text()));
        return false;
    } else {
        return true;
    }
}

void BancoDados::fecharConexao()
{
    db.close();
}

bool BancoDados::isOpen()
{
    if(db.isOpen())
        return true;
    return false;
}

QString BancoDados::formatarData(QString _dataToFormat)
{
    QDate _dataEdit;
    _dataEdit.fromString(_dataToFormat);
    return QString(_dataEdit.toString("DD/MM/YYYY"));
}

QMap<int, CadastroEmpresa *> BancoDados::listarEmpresas()
{
    QSqlQuery consulta;
    QMap<int, CadastroEmpresa*> mapEmpresas;
    QString query = "SELECT NUMEMP, APEEMP, NOMEMP FROM R030EMP WHERE NUMEMP > 1000 ORDER BY NUMEMP";
    consulta.prepare(query);
    if(!consulta.exec()){
        QMessageBox::critical(0, QString("Banco de Dados"),
                              QString("Não foi possível executar consulta de lista de empresas!\n%1")
                              .arg(consulta.lastError().text()));
    } else {
        int index = 0;
        while (consulta.next()) {
            index++;
            mapEmpresas.insert(index,
                               new CadastroEmpresa(consulta.value(0).toString(),
                                                   consulta.value(1).toString(),
                                                   consulta.value(2).toString()));
        }
    }
    return mapEmpresas;
}

QMap<int, CadastroFilial *> BancoDados::listarFiliais(QString _empresa)
{
    QMap<int, CadastroFilial*> mapFiliais;
    if(_empresa.isEmpty() || _empresa.endsWith(" ")){
        QMessageBox::critical(0, QString("Banco de Dados"),
                              QString("A empresa não foi definida para criar uma query para consulta!"),"OK");
    } else {
        QSqlQuery consulta;
        QString query = QString("SELECT NUMEMP, CODFIL, TIPFIL, RAZSOC, NOMFIL, NUMCGC, INSEST "
                                "FROM R030FIL "
                                "WHERE NUMEMP = %0 ORDER BY CODFIL").arg(_empresa);
        consulta.prepare(query);
        if(!consulta.exec()){
            QMessageBox::critical(0, QString("Banco de Dados"),
                                  QString("Não foi possível executar consulta da lista de filais!\n%1")
                                  .arg(consulta.lastError().text()));
        } else {
            int index = 0;
            while (consulta.next()) {
                index++;
                mapFiliais.insert(index,
                                  new CadastroFilial(
                                      consulta.value(0).toString(),
                                      consulta.value(1).toString(),
                                      consulta.value(2).toString(),
                                      consulta.value(3).toString(),
                                      consulta.value(4).toString(),
                                      consulta.value(5).toString(),
                                      consulta.value(6).toString()));
            }
        }
    }
    return mapFiliais;
}

QMap<int, CadastroColaborador *> BancoDados::listarColaboradores(QString _empresa, QString _filial,QString _dtIni,QString _dtFim)
{
    QString query;
    QMap<int, CadastroColaborador*> mapColaboradores;
    if(_empresa.isEmpty() || _empresa.endsWith(" ")){
        QMessageBox::critical(0, QString("Banco de Dados"),
                              QString("A empresa não foi definida para criar uma query para consulta!"),"OK");
    } else {
        QSqlQuery consulta;
        if(_empresa.isEmpty() || _filial.count() == 0 || _filial.endsWith(" ")) {
            query = QString("SELECT FUN.NUMEMP, "
                            "FUN.CODFIL, "
                            "FUN.NUMCAD, "
                            "FUN.NOMFUN, "
                            "FUN.NUMCAD, "
                            "FUN.NUMCPF, "
                            "FUN.NUMPIS, "
                            "DATNAS = CONVERT(VARCHAR(10),FUN.DATNAS,103), "
                            "DATADM = CONVERT(VARCHAR(10),FUN.DATADM,103), "
                            "FUN.TIPSEX, "
                            "ORN.NOMLOC, "
                            "FIL.NOMFIL, "
                            "FUN.NUMCRA, "
                            "FUN.CONRHO, "
                            "FUN.SITAFA, "
                            "CAR.TITRED "
                            "FROM R034FUN FUN "
                            "LEFT JOIN R016ORN ORN ON (ORN.TABORG = FUN.TABORG AND ORN.NUMLOC = FUN.NUMLOC) "
                            "LEFT JOIN R030FIL FIL ON (FIL.NUMEMP = FUN.NUMEMP AND FIL.CODFIL = FUN.CODFIL) "
                            "LEFT JOIN R024CAR CAR ON (CAR.ESTCAR = FUN.ESTCAR AND CAR.CODCAR = FUN.CODCAR) "
                            "WHERE FUN.NUMEMP = %0 AND FUN.CONRHO = 2 AND FUN.DATADM >= '%1' AND FUN.DATADM <= '%2' "
                            "AND FUN.SITAFA = 1 AND FUN.TIPCON = 1 ORDER BY FUN.NUMEMP, FUN.CODFIL, FUN.NUMCAD").arg(_empresa).arg(_dtIni).arg(_dtFim);
        } else {
            query = QString("SELECT FUN.NUMEMP, "
                            "FUN.CODFIL, "
                            "FUN.NUMCAD, "
                            "FUN.NOMFUN, "
                            "FUN.NUMCPF, "
                            "FUN.NUMPIS, "
                            "DATNAS = CONVERT(VARCHAR(10),FUN.DATNAS,103), "
                            "DATADM = CONVERT(VARCHAR(10),FUN.DATADM,103), "
                            "FUN.TIPSEX, "
                            "ORN.NOMLOC, "
                            "FIL.NOMFIL, "
                            "FUN.NUMCRA, "
                            "FUN.CONRHO, "
                            "FUN.SITAFA, "
                            "CAR.TITRED "
                            "FROM R034FUN FUN "
                            "LEFT JOIN R016ORN ORN ON (ORN.TABORG = FUN.TABORG AND ORN.NUMLOC = FUN.NUMLOC) "
                            "LEFT JOIN R030FIL FIL ON (FIL.NUMEMP = FUN.NUMEMP AND FIL.CODFIL = FUN.CODFIL) "
                            "LEFT JOIN R024CAR CAR ON (CAR.ESTCAR = FUN.ESTCAR AND CAR.CODCAR = FUN.CODCAR) "
                            "WHERE FUN.NUMEMP = %0 AND FUN.CONRHO = 2 AND FUN.DATADM >= '%1' AND FUN.DATADM <= '%2' "
                            "AND FUN.SITAFA = 1 AND FUN.TIPCON = 1 AND FUN.CODFIL = %3 ORDER BY FUN.NUMEMP, FUN.CODFIL, FUN.NUMCAD").arg(_empresa).arg(_dtIni).arg(_dtFim).arg(_filial);
        }

        consulta.prepare(query);
        if(!consulta.exec()){
            QMessageBox::critical(0, QString("Banco de Dados"),
                                  QString("Não foi possível executar consulta da lista de filais!\n%1")
                                  .arg(consulta.lastError().text()));
        } else {
            int index = 0;
            while (consulta.next()) {
                index++;
                mapColaboradores.insert(index,
                                        new CadastroColaborador(consulta.value(0).toString(),
                                                                consulta.value(1).toString(),
                                                                consulta.value(2).toString(),
                                                                consulta.value(3).toString(),
                                                                consulta.value(4).toString(),
                                                                consulta.value(5).toString(),
                                                                consulta.value(6).toString(),
                                                                consulta.value(7).toString(),
                                                                consulta.value(8).toString(),
                                                                consulta.value(9).toString(),
                                                                consulta.value(10).toString().toUpper(),
                                                                consulta.value(11).toString(),
                                                                consulta.value(12).toString(),
                                                                consulta.value(13).toString(),
                                                                consulta.value(14).toString()));
            }
        }
    }
    return mapColaboradores;
}

