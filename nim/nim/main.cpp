/****************************************************************
**
** Qt tutorial 14
**
****************************************************************/

#include <qapplication.h>

#include "gameborad.h"


int main( int argc, char **argv )
{
    QApplication::setColorSpec( QApplication::CustomColor );
    QApplication a( argc, argv );

    GameBoard gb;
    gb.setGeometry( 100, 100, 700, 700 );
    a.setMainWidget( &gb );
    gb.show();
    return a.exec();
}
