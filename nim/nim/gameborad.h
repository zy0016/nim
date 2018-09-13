/***************************************************************
**
** Definition of GameBoard class, Qt tutorial 14
**
****************************************************************/

#ifndef GAMEBRD_H
#define GAMEBRD_H

#include <qwidget.h>
#include "nim.h"

class QPushButton;
//class LCDRange;
class QLCDNumber;
class NimField;

//#include "lcdrange.h"
//#include "cannon.h"


class GameBoard : public QWidget
{
    Q_OBJECT
public:
    GameBoard( QWidget *parent=0, const char *name=0 );

protected slots:
    //void  fire();
    void  Prompt();
    void  Contrition();
    void  NewGame();

private:
    //QLCDNumber  *hits;
    //QLCDNumber  *shotsLeft;
    NimField * qNimChess;
};
#endif // GAMEBRD_H
