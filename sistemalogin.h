#ifndef SISTEMALOGIN_H
#define SISTEMALOGIN_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>

#include "desktophome.h"

namespace Ui {
class SistemaLogin;
}

class SistemaLogin : public QWidget
{
    Q_OBJECT

public:
    explicit SistemaLogin(QWidget *parent = 0);
    ~SistemaLogin();

    void setUsuarioInformado(const QString &_usuarioInformado);

    QString getUsuarioInformado() const;


private slots:
    void iniciaConfiguracoes();
    void abrirJanelaHome();
    bool autenticarUsuario(QString usr,QString pass);

    void focusCampoUsuarioPressionado();
    void focusCampoSenhaPressionado();
    void focusAutomatico();

private:
    QString usuarioInformado;
    Ui::SistemaLogin *ui;
};

#endif // SISTEMALOGIN_H
