/****************************************************************
**
** Definition of NimField class, Qt tutorial 14
**
****************************************************************/

#ifndef _NIM_H_
#define _NIM_H_

class QTimer;


#include <qwidget.h>

#define        HX1                    11                                    //????????
#define        HY1                    3                                    //????????
#define        BH                    38                                    //???
#define        BW                    BH                                    //???
#define        FLASHNUM            6                                    //???????

#define        UP                    1//????
#define        DOWN                2//????
#define        RED                    1//???-??
#define        BLACK                2//???-??

#define        EASY                0//????
#define        MIDDLE                1//????
#define        HARD                2//????

#define        CASENUM                8//??
#define        REMAINNUM            196

typedef struct tagPOINT
{
    long x;
    long y;
}POINT;

typedef    struct
{
    POINT    red;                //?????????
    POINT    redbak;                //????????????
    POINT    redregret;            //????????????????
    POINT    black;                //?????????
    POINT    blackbak;            //????????????
    POINT    blackregret;        //????????????????
}CHESS;

typedef    struct
{
    int red;                    //????(????)
    int black;                    //????(????)
    int step;                    //????(??????)
    int stepbak;                //??????
    int x;                        //?????.????????????????
}PLACE;
struct REMAIN
{
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
};

typedef enum
{
    People_Computer,
	People_People
}GAMETYPE;

typedef enum
{
    People_Red,
	People_Black
}PEOPLE_PLAY;

typedef enum
{
    Difficult_Easy,
	Difficult_Middle,
	Difficult_Hard
}CHESS_DIFFICULTY;

class NimField : public QWidget
{
    Q_OBJECT
public:
    NimField( QWidget *parent=0, const char *name=0 );

//     int   angle() const { return ang; }
//     int   force() const { return f; }
//     bool  gameOver() const { return gameEnded; }
//     bool  isShooting() const;
//     QSize sizeHint() const;
//     QSizePolicy sizePolicy() const;

public slots:
//     void  setAngle( int degrees );
//     void  setForce( int newton );
//     void  shoot();
//     void  newTarget();
//     void  setGameOver();
//     void  restartGame();
    void NewGame();
	void Contrition();
	void Prompt();

private slots:
    //void  moveShot();
    void TimerMoveChessman();
signals:
//     void  hit();
//     void  missed();
//     void  angleChanged( int );
//     void  forceChanged( int );
//     void  canShoot( bool );

protected:
     void  paintEvent( QPaintEvent * );
     void  mousePressEvent( QMouseEvent * );
     void  mouseMoveEvent( QMouseEvent * );
//     void  mouseReleaseEvent( QMouseEvent * );

private:
    void InitChessman();
    int GetChessNum(const QPoint &point);
    void DrawSign(int icurcol);
	int GetChessStep(QPoint point,GAMETYPE itype,int icolabs,PEOPLE_PLAY bothsides);
	int MoveChess(int itype,int icol,int iway,int istep);
	bool IfGameOver();
	bool Start(CHESS_DIFFICULTY idifficulty,int * ix,int * istep);
	int just(CHESS_DIFFICULTY idifficulty,int * x,int * istep);
	int findchess(CHESS_DIFFICULTY idifficulty,int * ix,int * istep);
	int equation(CHESS_DIFFICULTY idifficulty,int iCase,int * ix,int * istep);
	void DrawChessSingle(int icol);
	void flashchess(int x);
//     void  paintShot( QPainter * );
//     void  paintTarget( QPainter * );
//     void  paintBarrier( QPainter * );
//     void  paintCannon( QPainter * );
//     QRect cannonRect() const;
//     QRect shotRect() const;
//     QRect targetRect() const;
//     QRect barrierRect() const;
//     bool  barrelHit( const QPoint & ) const;

    int iStep;//move step
    int iCurSelCol;//current select col(opposite)
	int iCurSelColAb;//current select col(absolute)
    CHESS chess[CASENUM];    //16??????
    PLACE splace[CASENUM];//?????????

	GAMETYPE eGameType;
	bool bComputerPlay;//true:computer go,false:computer wait
	PEOPLE_PLAY ePeople_Play;
	QTimer * autoTimer;
	CHESS_DIFFICULTY eDifficult;
	int imovechessmanx;
	QString qClew;
	QString qPrompt;
	bool bRegret;//true:regret,false:restore
	bool bStartFlashChessman;//true:start flash one chessman,false:flash end.
	int iFlashnum;//flash chessman number;
	int iClewNum;
	////////////////////////
    /*int ang;
    int f;

    int timerCount;
    //QTimer * autoShootTimer;
    float shoot_ang;
    float shoot_f;

    QPoint target;

    bool gameEnded;
    bool barrelPressed;*/
};




static struct REMAIN remain[] = //196
{
    {0,0,0,0,0,1,2,3},
    {0,0,0,0,0,1,4,5},
    {0,0,0,0,0,2,4,6},
    {0,0,0,0,0,3,5,6},
    {0,0,0,0,1,2,5,6},
    {0,0,0,0,1,3,4,6},
    {0,0,0,0,2,3,4,5},
    {0,0,0,1,1,1,2,3},
    {0,0,0,1,1,1,4,5},
    {0,0,0,1,1,2,4,6},
    {0,0,0,1,1,3,5,6},
    {0,0,0,1,2,2,2,3},
    {0,0,0,1,2,2,4,5},
    {0,0,0,1,2,3,3,3},
    {0,0,0,1,2,3,4,4},
    {0,0,0,1,2,3,5,5},
    {0,0,0,1,2,3,6,6},
    {0,0,0,1,3,3,4,5},
    {0,0,0,1,4,4,4,5},
    {0,0,0,1,4,5,5,5},
    {0,0,0,1,4,5,6,6},
    {0,0,0,2,2,2,4,6},
    {0,0,0,2,2,3,5,6},
    {0,0,0,2,3,3,4,6},
    {0,0,0,2,4,4,4,6},
    {0,0,0,2,4,5,5,6},
    {0,0,0,2,4,6,6,6},
    {0,0,0,3,3,3,5,6},
    {0,0,0,3,4,4,5,6},
    {0,0,0,3,5,5,5,6},
    {0,0,0,3,5,6,6,6},
    {0,0,1,1,1,2,5,6},
    {0,0,1,1,1,3,4,6},
    {0,0,1,1,2,3,4,5},
    {0,0,1,2,2,2,5,6},
    {0,0,1,2,2,3,4,6},
    {0,0,1,2,3,3,5,6},
    {0,0,1,2,4,4,5,6},
    {0,0,1,2,5,5,5,6},
    {0,0,1,2,5,6,6,6},
    {0,0,1,3,3,3,4,6},
    {0,0,1,3,4,4,4,6},
    {0,0,1,3,4,5,5,6},
    {0,0,1,3,4,6,6,6},
    {0,0,2,2,2,3,4,5},
    {0,0,2,3,3,3,4,5},
    {0,0,2,3,4,4,4,5},
    {0,0,2,3,4,5,5,5},
    {0,0,2,3,4,5,6,6},
    {0,1,1,1,1,1,2,3},
    {0,1,1,1,1,1,4,5},
    {0,1,1,1,1,2,4,6},
    {0,1,1,1,1,3,5,6},
    {0,1,1,1,2,2,2,3},
    {0,1,1,1,2,2,4,5},
    {0,1,1,1,2,3,3,3},
    {0,1,1,1,2,3,4,4},
    {0,1,1,1,2,3,5,5},
    {0,1,1,1,2,3,6,6},
    {0,1,1,1,3,3,4,5},
    {0,1,1,1,4,4,4,5},
    {0,1,1,1,4,5,5,5},
    {0,1,1,1,4,5,6,6},
    {0,1,1,2,2,2,4,6},
    {0,1,1,2,2,3,5,6},
    {0,1,1,2,3,3,4,6},
    {0,1,1,2,4,4,4,6},
    {0,1,1,2,4,5,5,6},
    {0,1,1,2,4,6,6,6},
    {0,1,1,3,3,3,5,6},
    {0,1,1,3,4,4,5,6},
    {0,1,1,3,5,5,5,6},
    {0,1,1,3,5,6,6,6},
    {0,1,2,2,2,2,2,3},
    {0,1,2,2,2,2,4,5},
    {0,1,2,2,2,3,3,3},
    {0,1,2,2,2,3,4,4},
    {0,1,2,2,2,3,5,5},
    {0,1,2,2,2,3,6,6},
    {0,1,2,2,3,3,4,5},
    {0,1,2,2,4,4,4,5},
    {0,1,2,2,4,5,5,5},
    {0,1,2,2,4,5,6,6},
    {0,1,2,3,3,3,3,3},
    {0,1,2,3,3,3,4,4},
    {0,1,2,3,3,3,5,5},
    {0,1,2,3,3,3,6,6},
    {0,1,2,3,4,4,4,4},
    {0,1,2,3,4,4,5,5},
    {0,1,2,3,4,4,6,6},
    {0,1,2,3,5,5,5,5},
    {0,1,2,3,5,5,6,6},
    {0,1,2,3,6,6,6,6},
    {0,1,3,3,3,3,4,5},
    {0,1,3,3,4,4,4,5},
    {0,1,3,3,4,5,5,5},
    {0,1,3,3,4,5,6,6},
    {0,1,4,4,4,4,4,5},
    {0,1,4,4,4,5,5,5},
    {0,1,4,4,4,5,6,6},
    {0,1,4,5,5,5,5,5},
    {0,1,4,5,5,5,6,6},
    {0,1,4,5,6,6,6,6},
    {0,2,2,2,2,2,4,6},
    {0,2,2,2,2,3,5,6},
    {0,2,2,2,3,3,4,6},
    {0,2,2,2,4,4,4,6},
    {0,2,2,2,4,5,5,6},
    {0,2,2,2,4,6,6,6},
    {0,2,2,3,3,3,5,6},
    {0,2,2,3,4,4,5,6},
    {0,2,2,3,5,5,5,6},
    {0,2,2,3,5,6,6,6},
    {0,2,3,3,3,3,4,6},
    {0,2,3,3,4,4,4,6},
    {0,2,3,3,4,5,5,6},
    {0,2,3,3,4,6,6,6},
    {0,2,4,4,4,4,4,6},
    {0,2,4,4,4,5,5,6},
    {0,2,4,4,4,6,6,6},
    {0,2,4,5,5,5,5,6},
    {0,2,4,5,5,6,6,6},
    {0,2,4,6,6,6,6,6},
    {0,3,3,3,3,3,5,6},
    {0,3,3,3,4,4,5,6},
    {0,3,3,3,5,5,5,6},
    {0,3,3,3,5,6,6,6},
    {0,3,4,4,4,4,5,6},
    {0,3,4,4,5,5,5,6},
    {0,3,4,4,5,6,6,6},
    {0,3,5,5,5,5,5,6},
    {0,3,5,5,5,6,6,6},
    {0,3,5,6,6,6,6,6},
    {1,1,1,1,1,2,5,6},
    {1,1,1,1,1,3,4,6},
    {1,1,1,1,2,3,4,5},
    {1,1,1,2,2,2,5,6},
    {1,1,1,2,2,3,4,6},
    {1,1,1,2,3,3,5,6},
    {1,1,1,2,4,4,5,6},
    {1,1,1,2,5,5,5,6},
    {1,1,1,2,5,6,6,6},
    {1,1,1,3,3,3,4,6},
    {1,1,1,3,4,4,4,6},
    {1,1,1,3,4,5,5,6},
    {1,1,1,3,4,6,6,6},
    {1,1,2,2,2,3,4,5},
    {1,1,2,3,3,3,4,5},
    {1,1,2,3,4,4,4,5},
    {1,1,2,3,4,5,5,5},
    {1,1,2,3,4,5,6,6},
    {1,2,2,2,2,2,5,6},
    {1,2,2,2,2,3,4,6},
    {1,2,2,2,3,3,5,6},
    {1,2,2,2,4,4,5,6},
    {1,2,2,2,5,5,5,6},
    {1,2,2,2,5,6,6,6},
    {1,2,2,3,3,3,4,6},
    {1,2,2,3,4,4,4,6},
    {1,2,2,3,4,5,5,6},
    {1,2,2,3,4,6,6,6},
    {1,2,3,3,3,3,5,6},
    {1,2,3,3,4,4,5,6},
    {1,2,3,3,5,5,5,6},
    {1,2,3,3,5,6,6,6},
    {1,2,4,4,4,4,5,6},
    {1,2,4,4,5,5,5,6},
    {1,2,4,4,5,6,6,6},
    {1,2,5,5,5,5,5,6},
    {1,2,5,5,5,6,6,6},
    {1,2,5,6,6,6,6,6},
    {1,3,3,3,3,3,4,6},
    {1,3,3,3,4,4,4,6},
    {1,3,3,3,4,5,5,6},
    {1,3,3,3,4,6,6,6},
    {1,3,4,4,4,4,4,6},
    {1,3,4,4,4,5,5,6},
    {1,3,4,4,4,6,6,6},
    {1,3,4,5,5,5,5,6},
    {1,3,4,5,5,6,6,6},
    {1,3,4,6,6,6,6,6},
    {2,2,2,2,2,3,4,5},
    {2,2,2,3,3,3,4,5},
    {2,2,2,3,4,4,4,5},
    {2,2,2,3,4,5,5,5},
    {2,2,2,3,4,5,6,6},
    {2,3,3,3,3,3,4,5},
    {2,3,3,3,4,4,4,5},
    {2,3,3,3,4,5,5,5},
    {2,3,3,3,4,5,6,6},
    {2,3,4,4,4,4,4,5},
    {2,3,4,4,4,5,5,5},
    {2,3,4,4,4,5,6,6},
    {2,3,4,5,5,5,5,5},
    {2,3,4,5,5,5,6,6},
    {2,3,4,5,6,6,6,6}
};

#endif // _NIM_H_
