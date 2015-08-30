#include "sistemalogin.h"
#include <QApplication>

#include <QDesktopWidget>
#include <bancodados.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget d;
    QRect area = d.availableGeometry();
    QPoint centro = area.center();
    BancoDados * db = new BancoDados;
    db->abrirConexao();
    SistemaLogin w;
    w.move(centro.x()-w.width()*0.5,centro.y()-w.height()*0.5);
    w.show();

    return a.exec();
}
