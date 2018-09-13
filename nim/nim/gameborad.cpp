/***************************************************************
**
** Implementation of GameBoard class, Qt tutorial 14
**
****************************************************************/

#include "gameborad.h"
#include <qfont.h>
#include <qapplication.h>
#include <qlabel.h>
#include <qaccel.h>
#include <qpushbutton.h>
#include <qlcdnumber.h>
#include <qlayout.h>
#include <qvbox.h>

//#include "lcdrange.h"
//#include "cannon.h"

GameBoard::GameBoard( QWidget *parent, const char *name )
        : QWidget( parent, name )
{
    //new game
    QPushButton *QBNewGame = new QPushButton( "&New Game", this, "NewGame" );
    QBNewGame->setFont( QFont( "Times", 18, QFont::Bold ) );
    connect( QBNewGame, SIGNAL(clicked()), this, SLOT(NewGame()) );
    //contrition
	QPushButton *QBContrition = new QPushButton( "&Contrition", this, "Contrition" );
    QBContrition->setFont( QFont( "Times", 18, QFont::Bold ) );
    connect( QBContrition, SIGNAL(clicked()), this, SLOT(Contrition()) );
    //prompt
	QPushButton *QBPrompt = new QPushButton( "&Prompt", this, "Prompt" );
    QBPrompt->setFont( QFont( "Times", 18, QFont::Bold ) );
    connect( QBPrompt, SIGNAL(clicked()), this, SLOT(Prompt()) );
	//exit
	QPushButton *QBQuit = new QPushButton( "&Quit", this, "Quit" );
    QBQuit->setFont( QFont( "Times", 18, QFont::Bold ) );
    connect( QBQuit, SIGNAL(clicked()), qApp, SLOT(quit()) );
    ///////////////////////////////////////////////////////////////

    //QVBox *box = new QVBox( this, "cannonFrame" );
    //box->setFrameStyle( QFrame::WinPanel | QFrame::Sunken );

    QGridLayout *grid = new QGridLayout( this, 2, 2, 10 );
	qNimChess = new NimField( this, "Nimchess" );
    //grid->addWidget( QBNewGame, 0, 1 );
    //grid->addWidget( QBContrition, 0, 2 );
	//grid->addWidget( QBPrompt, 0, 3 );
    //grid->addWidget( QBQuit, 0, 4 );
    //grid->setColStretch( 1, 10 );

    //QVBoxLayout *leftBox = new QVBoxLayout;
    //grid->addLayout( leftBox, 1, 0 );
#if 0
    //This code is ok,too.
    QHBoxLayout *topBox = new QHBoxLayout;
    grid->addLayout( topBox, 0, 0 );
    topBox->addWidget( QBNewGame );
    topBox->addWidget( QBContrition );
    topBox->addWidget( QBPrompt );
    topBox->addWidget( QBQuit );
#else
    grid->addWidget( QBNewGame, 0, 0 );
    grid->addWidget( QBContrition, 0, 1);
	grid->addWidget( QBPrompt, 0, 2 );
    grid->addWidget( QBQuit, 0, 3 );

	//QGridLayout *gridChess = new QGridLayout( this, 1, 1, 10 );
	grid->addWidget( qNimChess, 1, 1 );
	grid->setColStretch( 1, 10 );
#endif
	//topBox->addWidget( shotsLeftL );
    //topBox->addStretch( 1 );
    //topBox->addWidget( NewGame );

    //angle->setFocus();

    NewGame();
}

void GameBoard::NewGame()
{
    //NimField * qNimChess = new NimField;
    qNimChess->NewGame();
}
void GameBoard::Contrition()
{
    qNimChess->Contrition();
}
void GameBoard::Prompt()
{
    qNimChess->Prompt();
}
