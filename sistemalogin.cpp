#include "sistemalogin.h"
#include "ui_sistemalogin.h"
int numeroTentativas;

SistemaLogin::SistemaLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SistemaLogin)
{
    ui->setupUi(this); //iniciaConfiguracoes();


}

SistemaLogin::~SistemaLogin()
{
    delete ui;
}

void SistemaLogin::iniciaConfiguracoes()
{
    connect(ui->botaoEntrar,SIGNAL(clicked(bool)),this,SLOT(abrirJanelaHome()));
    connect(ui->botaoEntrar,SIGNAL(pressed()),this,SLOT(abrirJanelaHome()));
    connect(ui->botaoSair,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->campoUsuario,SIGNAL(returnPressed()),this,SLOT(focusAutomatico()));
    connect(ui->campoSenha,SIGNAL(returnPressed()),this,SLOT(focusAutomatico()));
}

void SistemaLogin::abrirJanelaHome()
{
    DesktopHome * janelaDh = new DesktopHome(getUsuarioInformado());
    QRect areaJanela = this->geometry();
    QPoint centralizar = areaJanela.center();
    connect(janelaDh,SIGNAL(fecharHome()), this, SLOT(show()));
    janelaDh->move(centralizar.x()-janelaDh->width()*0.5,centralizar.y()-janelaDh->height()*0.5);
    janelaDh->show();
    janelaDh->activateWindow();
    this->close();
}

bool SistemaLogin::autenticarUsuario(QString usr, QString pass)
{
    if(usr.isEmpty()){
        return false;
    } else {
        if(usr.endsWith("00494134305") && pass.endsWith("complexa")){
            return true;
        } else {
            return false;
        }
    }
}

void SistemaLogin::focusCampoUsuarioPressionado()
{
    QString campoStrUsu = ui->campoUsuario->text().trimmed();
    QRegExp rx("(\\d+)");
    QStringList listCaracter;
    int pos = 0;
    if(campoStrUsu.isEmpty() || campoStrUsu.contains("..-")){
        ui->campoUsuario->setFocus();
    } else {
        while ((pos = rx.indexIn(campoStrUsu, pos)) != -1) {
            listCaracter << rx.cap(1);
            pos += rx.matchedLength();
        }
        QString numCpf = QString("%0%1%2%3").arg(listCaracter.at(0))
                .arg(listCaracter.at(1))
                .arg(listCaracter.at(2))
                .arg(listCaracter.at(3));

        if(numCpf.isEmpty() || numCpf.contains(".")){
            QMessageBox::information(this, QString("Autenticação do usuário"),QString("CPF inválido!"),"OK");
            ui->campoUsuario->setEnabled(true);
            ui->campoUsuario->setFocus();
        } else {
            setUsuarioInformado(numCpf);
            ui->campoUsuario->setEnabled(true);
            ui->campoSenha->setFocus();
        }
    }
}

void SistemaLogin::focusCampoSenhaPressionado()
{
    if( numeroTentativas >= 5){
        QMessageBox::information(this, QString("Erro de Autenticação"),QString("Número de tentativas esgotadas!"),"OK");
        this->close();
    } else {
        if(!autenticarUsuario(getUsuarioInformado(),ui->campoSenha->text())){
            numeroTentativas++;
            ui->mensagemUsuario->setText(QString("[!] Tentativa %0! Usuário não autorizado!").arg(numeroTentativas));
            ui->campoSenha->clear();
            ui->campoSenha->setFocus();
        } else {
            abrirJanelaHome();
        }
    }
}

void SistemaLogin::focusAutomatico()
{
    //
}

QString SistemaLogin::getUsuarioInformado() const
{
    return usuarioInformado;
}

void SistemaLogin::setUsuarioInformado(const QString &_usuarioInformado)
{
    usuarioInformado = _usuarioInformado;
}

