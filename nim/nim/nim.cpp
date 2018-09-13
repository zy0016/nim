/****************************************************************
**
** Implementation NimField class, Qt tutorial 14
**
****************************************************************/

#include "nim.h"
#include <qtimer.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qdatetime.h>
#include <qcursor.h>
#include <math.h>
#include <stdlib.h>


NimField::NimField( QWidget *parent, const char *name )
        : QWidget( parent, name )
{
//     ang = 45;
//     f = 0;
//     timerCount = 0;
//     shoot_ang = 0;
//     shoot_f = 0;
//     target = QPoint( 0, 0 );
//     gameEnded = FALSE;
//     barrelPressed = FALSE;
    setPalette( QPalette( QColor( 250, 250, 200) ) );
    //newTarget();
	/////////////////////////
	iCurSelCol = 0;
	iCurSelColAb = 8;
	eGameType = People_Computer;
	bComputerPlay = false;
	autoTimer = new QTimer( this, "movement handler" );
	eDifficult = Difficult_Easy;
	imovechessmanx = 0;
	iStep = 0;
	qClew = "";
	qPrompt = "";
	iClewNum = 0;
	iFlashnum = 0;
	connect( autoTimer, SIGNAL(timeout()),this, SLOT(TimerMoveChessman()));
}

/*********************************************************************\
* Function       flashchess
* Purpose    ?????
* Params
* Return
* Remarks
**********************************************************************/
void NimField::flashchess(int x)
{
    static bool bBlack = false;
	QPainter p( this );
	
	if ((x < 0) || (x > CASENUM - 1))
	    return;
	p.setPen(NoPen);
	if (bBlack)
	    p.setBrush(red);
	else
	    p.setBrush(QColor( 250, 250, 200));
		
	p.drawPie(QRect(chess[x].red.x,chess[x].red.y,BW,BH),0,360 * 16);
	bBlack = !bBlack;
}

void NimField::TimerMoveChessman()
{
    int i;
    if ((eGameType == People_People) || (!bComputerPlay) || (!bStartFlashChessman))
	{
	    autoTimer->stop();
	    return;
	}
	if (iFlashnum < FLASHNUM)//fresh chessman
	{
	    iFlashnum++;
		flashchess(imovechessmanx);
		return;
	}
	if (iFlashnum == FLASHNUM)
	{
	    chess[imovechessmanx].red.y = chess[imovechessmanx].red.y + BH * iStep;//coordinate
        for (i = 0;i < CASENUM;i++)//regret chessman
		{
		    chess[i].blackbak.x = chess[i].black.x;
			chess[i].blackbak.y = chess[i].black.y;
			chess[i].redbak.x   = chess[i].red.x;
			chess[i].redbak.y   = chess[i].red.y;

			splace[i].red   = (chess[i].red.y - HY1) / BH;
			splace[i].black = CASENUM - (HY1 + BH * CASENUM - chess[i].black.y) / BH;
		}
		bRegret = true;
		bComputerPlay = false;

		DrawChessSingle(imovechessmanx);
	}
	if (IfGameOver() && !bComputerPlay)
	{
	    qClew = "You Fail!";
		qPrompt = "";
		autoTimer->stop();
		repaint();
	}
}
void NimField::NewGame()
{
	InitChessman();
	iClewNum = 0;
	iFlashnum = 0;
	if (autoTimer->isActive())
	{
	    autoTimer->stop();
	}
	eGameType = People_Computer;
	switch (eGameType)
	{
	case People_Computer:
	    bComputerPlay = false;
		bRegret = true;
		//ChessMenu
	    break;
	case People_People:
	    ePeople_Play = People_Black;
	    break;
	}
	qClew = "";
	qPrompt = "";
	repaint();
	//emit canShoot( TRUE );
}

void NimField::Prompt()
{
    int x,step;
	char clew[40] = "";
    if (IfGameOver())
	{
	    qClew = "Game Over!";
		qPrompt = "";
		repaint();
		return;
	}
	switch (eDifficult)
	{
	case Difficult_Easy:
	    Start(Difficult_Hard,&x,&step);//compute how to play
		sprintf(clew,"Move %d col,move up %d row",x + 1,step);

		qPrompt = clew;
		qWarning(qPrompt);
	    break;
	case Difficult_Middle:
	    if (iClewNum < 3)
		{
            Start(Difficult_Hard,&x,&step);//compute how to play
		    sprintf(clew,"Move %d col,move up %d row",x + 1,step);
			iClewNum++;
			qPrompt = clew;
		}
		else
		{
		    qPrompt = "Without prompt.";
		}
	    break;
	case Difficult_Hard:
	    qPrompt = "Without prompt in hard level";
	    break;
	}
	repaint();
}
void NimField::Contrition()
{
    int i;
    if (bRegret)
	{
	    for (i = 0;i < CASENUM;i++)
		{
		    chess[i].black.y = chess[i].blackregret.x;
			chess[i].black.y = chess[i].blackregret.y;
			chess[i].red.x   = chess[i].redregret.x;
			chess[i].red.y   = chess[i].redregret.y;
		}
	}
	else
	{
	    for (i = 0;i < CASENUM;i++)
		{
		    chess[i].black.x = chess[i].blackbak.x;
			chess[i].black.y = chess[i].blackbak.y;
			chess[i].red.x   = chess[i].redbak.x;
			chess[i].red.y   = chess[i].redbak.y;
		}
	}
	if (eGameType == People_People)
	{
	    switch (ePeople_Play)
		{
		case People_Red:
		    ePeople_Play = People_Black;
		    break;
		case People_Black:
		    ePeople_Play = People_Red;
		    break;
		}
	}
	else
	{
	    bComputerPlay = false;
	}
	bRegret = !bRegret;
	repaint();
}

void NimField::mousePressEvent( QMouseEvent * e)
{
    int i;
    //qWarning("mousePressEvent,e->x:%d,e->y:%d",e->x(),e->y());
	if ((eGameType == People_Computer) && bComputerPlay)
	    return;
    int itempcol = GetChessNum(e->pos());
	//qWarning("mousePressEvent itempcol:%d",itempcol);
	if (itempcol != -1)//selected one chessman
	{
        iCurSelColAb = itempcol;
		if (iCurSelColAb < CASENUM)//selected red
		{
		    //when the game are between people and computer,
			//if user select red chessman,the system will not work.
		    if (People_Computer == eGameType)
			    return ;
			//when the game are between people and people,
			//when the black will play,if user select red chessman,the system will not work.
		    if (ePeople_Play == People_Black)
			    return ;
			iCurSelCol = iCurSelColAb;
		}
		else//select black
		{
		    //when the game are between people and people,
			//when the red will play,if user select black chessman,the system will not work
            if (ePeople_Play == People_Red)
			    return ;

			iCurSelCol = iCurSelColAb - CASENUM;
		}
		DrawSign(iCurSelCol);//draw the sign to indication
	}
	else//without select chessman,click the chessboard
	{
	    iStep = GetChessStep(e->pos(),eGameType,iCurSelColAb,ePeople_Play);
		if (iStep == 0)//the where mouse click is invalid
		    return;

		for (i = 0;i < CASENUM;i++)//save the chessman place to regret
		{
		    chess[i].blackregret.x = chess[i].black.x;
			chess[i].blackregret.y = chess[i].black.y;
			chess[i].redregret.x   = chess[i].red.x;
			chess[i].redregret.y   = chess[i].red.y;
		}
		switch (eGameType)
		{
		case People_Computer:
		    MoveChess(People_Computer,iCurSelCol,UP,iStep);
			if (IfGameOver())//display "you win"
			{
			    autoTimer->stop();
				qClew = "You Win";
				qPrompt = "";
			    repaint();
			}
			else
			{
			    bComputerPlay = true;
				autoTimer->start(50);
				if (Start(eDifficult,&imovechessmanx,&iStep))//?????
                {
                    bStartFlashChessman = true;//??????
                    iFlashnum           = 0;//????????
                    bRegret             = true;
                }
			}
		    break;
		case People_People:
		    switch (ePeople_Play)
			{
			case People_Red://red play
			    MoveChess(eGameType,iCurSelCol,DOWN,iStep);
				ePeople_Play = People_Black;
				if (IfGameOver())
				{
				    qClew = "Red Win";
					qPrompt = "";
					repaint();
				}
			    break;
			case People_Black://black play
			    MoveChess(eGameType,iCurSelCol,UP,iStep);
				ePeople_Play = People_Red;
				if (IfGameOver())
				{
				    qClew = "Black Win";
					qPrompt = "";
					repaint();
				}
			    break;
			}
			bRegret = true;
		    break;
		}
		DrawChessSingle(iCurSelCol);
	}
}

/*********************************************************************\
* Function       DrawChessSingle
* Purpose     ??????,icol:??????
* Params
* Return
* Remarks
**********************************************************************/
void NimField::DrawChessSingle(int icol)
{
    //RECT rect;

    //SetRect(&rect,HX1 + BW * icol,HY1,HX1 + BW * (icol + 1),HY1 + BH * CASENUM);
    //InvalidateRect (hwnd,&rect,TRUE);
	repaint();
}

/*********************************************************************\
* Function       Start
* Purpose     ????
* Params     idifficulty:????,itype:????/????,icol:????????
* Return
* Remarks
**********************************************************************/
bool NimField::Start(CHESS_DIFFICULTY idifficulty,int * ix,int * istep)
{
    int i,x = -1,step = -1;

    for (i = 0;i < CASENUM;i++)
    {
        splace[i].red   = (chess[i].red.y - HY1) / BH;
        splace[i].black = CASENUM - (HY1 + BH * CASENUM - chess[i].black.y) / BH;
    }
    just(idifficulty,&x,&step);
    * ix    = x;
    * istep = step;
    if (x == -1)
    {
	    qClew = "Sorry,the game find a error and can not get correct result.";
		qPrompt = "";
		repaint();
        return false;
    }
    return true;
}
//*****************????**********************************************************************
//idifficulty:????
//ix:?????????,istep:?????????.
int NimField::just(CHESS_DIFFICULTY idifficulty,int * x,int * istep)
{
    int mLine = 0/*mLine:???????*/,i,j = 0,icase;
    int ix = 0,step = 0;

    for (i = 0;i < CASENUM;i++)
    {
        splace[i].x            = i;
        splace[i].step        = splace[i].black - splace[i].red - 1;
        splace[i].stepbak    = splace[i].step;
        if (splace[i].step > 0)
            mLine++;
    }
    if (mLine == 1)//???????
    {
        for (i = 0;i < CASENUM;i++)
            if (splace[i].step > 0)
            {
                * x        = i;
                * istep = splace[i].step;
                return 1;
            }
    }
    if (mLine == 2)//???????
    {
        for (icase = 1;icase < 7;icase++)//1-6
        {
            for (i = 0;i < CASENUM;i++)
                if (splace[i].step == icase)//?????eNum??,?????????eNum??
                {
                    for (j = 0;j < CASENUM;j++)
                        if (splace[j].step > icase)
                        {
                            * x        = j;
                            * istep = splace[j].step - icase;
                            return 1;
                        }
                }
        }
    }
    if ((mLine != 2) && (equation(idifficulty,mLine,&ix,&step) == 1))
    {
        * x        = ix;
        * istep = step;
        return 1;
    }
    if ((mLine != 2) && (findchess(idifficulty,&ix,&step) == 1))
    {
        * x        = ix;
        * istep = step;
        return 1;
    }
    else
    {
        srand((unsigned)time(NULL));
        j = rand() % CASENUM;                //?????????[0-7]
        if (splace[j].stepbak != 0)
        {
            * x = j;
            i    = rand() % 6 + 1;            //???????[1-6]
            if (i > splace[j].stepbak)        //???????[1-6]>???????
                * istep = splace[j].stepbak;
            else
                * istep = i;
            return 0;
        }
        for (i = 0;i < CASENUM;i++)
            if (splace[i].stepbak > 0)        //????????>0
            {
                * x = i;
                j    = rand() % 6 + 1;        //???????[1-6]
                if (j > splace[i].stepbak)    //???????[1-6]>???????
                    * istep = splace[i].stepbak;
                else
                    * istep = j;
                return 0;
            }
    }
    return 0;
}

//idifficulty:????
//ix:?????????,istep:?????????.
int NimField::findchess(CHESS_DIFFICULTY idifficulty,int * ix,int * istep)
{
    int i,x[CASENUM],j1,j2,iremain,isingle;
    int    idiff = 0,izero1,izero2;

    switch (idifficulty)//?????"????"???
    {
    case Difficult_Easy:
        idiff = 7;
        break;
    case Difficult_Middle:
        idiff = 31;
        break;
    case Difficult_Hard:
        idiff = REMAINNUM;
        break;
    }
    for (i = 0;i < idiff;i++)
    {
        x[0] = remain[i].a;
        x[1] = remain[i].b;
        x[2] = remain[i].c;
        x[3] = remain[i].d;
        x[4] = remain[i].e;
        x[5] = remain[i].f;
        x[6] = remain[i].g;
        x[7] = remain[i].h;

        izero1 = izero2 = 0;
        for (j1 = 0;j1 < CASENUM;j1++)
        {
            splace[j1].step = splace[j1].stepbak;    //??????

            if (x[j1] != 0)                            //????????????
                izero1++;
            if (splace[j1].step != 0)                //?????????
                izero2++;
        }
        if (izero1 > izero2)                        //????????????>????????????
            break;

        for (j1 = 0;j1 < CASENUM;j1++)                //???????,??????
        {
            for (j2 = 0;j2 < CASENUM;j2++)
            {
                if ((x[j1] != 0) && (x[j1] == splace[j2].step))
                {
                    x[j1]            = 0;
                    splace[j2].step = 0;
                }
            }
        }
        iremain = 0;
        isingle = -1;
        for (j1 = 0;j1 < CASENUM;j1++)
        {
            if (splace[j1].step != 0)
            {
                iremain++;        //?????????????,??1???,???????????
                isingle = j1;    //??????????????
            }
        }
        if (iremain == 1)//?????????
        {//??x???????????:1.CASENUM?????????????2.CASENUM???????
            * ix = splace[isingle].x;
            for (j1 = 0;j1 < CASENUM;j1++)
            {
                if (x[j1] != 0)    //1.CASENUM?????????????
                {
                    * istep = splace[isingle].stepbak - x[j1];
                    if (* istep > 0)
                        return 1;
                    else
                        return 0;
                }
            }
            * istep = splace[isingle].stepbak;//2.CASENUM???????
            return 1;
        }
        else if (iremain == 0)
            return 0;
    }
    return 0;
}

//idifficulty:????
//?????iCase
//1.iCase????,?????iCase - 2????????,???,????????????,??????;????0
//2.iCase????,?????iCase - 1????????,???,??????????,??????;????0
int NimField::equation(CHESS_DIFFICULTY idifficulty,int iCase,int * ix,int * istep)
{
    int x[CASENUM],i,j,jbak1,jbak2;

    switch(idifficulty)
    {
    case Difficult_Easy://????,????4??????
        if (iCase > 4)
            return 0;
        break;
    case Difficult_Middle://????,????6??????
        if (iCase > 6)
            return 0;
        break;
    case Difficult_Hard:
        break;
    }
    for ( i = 0;i < CASENUM ;i++ )
        x[i] = splace[i].step;

    for (i = 0;i < CASENUM;i++)//???????????0,???????????,???????
    {
        for (j = 0;j < CASENUM;j++)
        {
            if (i == j)
                continue;
            if ((x[i] == x[j])&&(x[i] != 0))
            {
                x[i] = 0;
                x[j] = 0;
            }
        }
    }
    j      = 0;
    jbak1 = -1;//?????????????
    jbak2 = -1;
    for (i = 0;i < CASENUM;i++)
    {
        if (x[i] != 0)
        {
            if (jbak1 == -1)
                jbak1 = i;
            else if (jbak2 == -1)
                jbak2 = i;
            j++;//????0???
        }
    }
    if ((j != 1) && (j != 2))
        return 0;

    if (iCase % 2 == 0)//??
    {
        if (j == 2)//iCase - 2????????
        {
            if (splace[jbak1].stepbak > splace[jbak2].stepbak)
                * ix = splace[jbak1].x;
            else
                * ix = splace[jbak2].x;

            * istep    = abs(splace[jbak1].stepbak - splace[jbak2].stepbak);
            return 1;
        }
    }
    else//??
    {
        if (j == 1)//iCase - 1????????
        {
            * ix    = splace[jbak1].x;
            * istep = splace[jbak1].stepbak;
            return 1;
        }
    }
    return 0;
}


/*********************************************************************\
* Function       IfGameOver
* Purpose     ??????(????1,????0)
* Params
* Return
* Remarks
**********************************************************************/
bool NimField::IfGameOver()
{
    int i;
    for (i = 0;i < CASENUM;i++)
        if (chess[i].red.y + BH != chess[i].black.y)
            return false;

    return true;
}
/*********************************************************************\
* Function       MoveChess
* Purpose     ????
* Params     itype:????(0:????,1????);col:????;iway:????;istep:??
* Return     ???????????1,????0
* Remarks
**********************************************************************/
int NimField::MoveChess(int itype,int icol,int iway,int istep)
{
    int i;
    if (itype == 0)//????
    {
        i = (chess[icol].black.y - chess[icol].red.y) / BH - 1;
        if (istep <= i)
        {
            chess[icol].black.y = chess[icol].black.y - istep * BH;
            return 1;
        }
    }
    else//????
    {
        i = (chess[icol].black.y - chess[icol].red.y) / BH - 1;
        switch (iway)
        {
        case UP:
            if (istep <= i)
                chess[icol].black.y = chess[icol].black.y - istep * BH;

            break;
        case DOWN:
            if (istep <= i)
                chess[icol].red.y = chess[icol].red.y + istep * BH;

            break;
        }
        return 1;
    }
    return 0;
}

/*********************************************************************\
* Function       GetChessStep
* Purpose     ??????????????????????????
* Params     itype:????/????;icolabs:?????,bothsides:??????:??/??
* Return     ??0???????????
* Remarks
**********************************************************************/
int NimField::GetChessStep(QPoint point,GAMETYPE itype,int icolabs,PEOPLE_PLAY bothsides)
{
    int icol,x,y,istep = 0;
    x = point.x();
    y = point.y();

    if (itype == People_Computer)//????
    {
        if ((-1 < icolabs) && (icolabs < CASENUM))//????,??????????????
            return 0;
        else//????
            icol = icolabs - CASENUM;

        if ((x < chess[icol].black.x) || (x > chess[icol].black.x + BW))
            return 0;//????????????????????
        if ((y < chess[icol].red.y)   || (y > chess[icol].black.y     ))
            return 0;//????????????????????????
        istep = (chess[icol].black.y - y) / BH + 1;
    }
    else//????
    {
        if ((-1 < icolabs) && (icolabs < CASENUM))//????
            icol = icolabs;
        else//????
            icol = icolabs - CASENUM;

        if ((x < chess[icol].black.x) || (x > chess[icol].black.x + BW))
            return 0;//????????????????????
        if ((y < chess[icol].red.y)   || (y > chess[icol].black.y      ))
            return 0;//????????????????????????
        switch (bothsides)
        {
        case People_Black:
            istep = (chess[icol].black.y - y) / BH + 1;
            break;
        case People_Red:
            istep = (y - chess[icol].red.y) / BH;
            break;
        }
    }
    return (istep);
}

void  NimField::mouseMoveEvent( QMouseEvent * e)
{
    qWarning("mouseMoveEvent,e->x:%d,e->y:%d",e->x(),e->y());
}

void NimField::DrawSign(int icurcol)
{
    QPainter p( this );

    p.setBrush(QColor( 250, 250, 200));
	p.setPen(NoPen);
    p.drawRect(HX1,HY1 + BH * CASENUM + 1,HX1 + BW * CASENUM,BH);
	//SetRect(&rect,HX1,HY1 + BH * CASENUM + 1,HX1 + BW * CASENUM + 1,HY1 + BH * (CASENUM + 1) + 1);
    //FillRect(hdc,&rect,hbr);
	//////////////////////////////////
	p.setBrush(black);
	p.setPen(NoPen);
	QPointArray point(1);
	point[0] = QPoint(HX1 + BW * icurcol + BW / 2,HY1 + BH * CASENUM + 1);
	point.putPoints(1,2,HX1 + BW * icurcol,HY1 + BH * (CASENUM + 1),
	                HX1 + BW * (icurcol + 1),HY1 + BH * (CASENUM + 1));

	p.drawPolygon(point);
}
/*********************************************************************\
* Function       GetChessNum
* Purpose     ??????????.?[0,7],?[8,15].??-1????????
* Params
* Return
* Remarks
**********************************************************************/
int NimField::GetChessNum(const QPoint &point)
{
    int i;
    for (i = 0;i < CASENUM;i++)
    {
        if ((chess[i].red.x < point.x()) && (point.x() < chess[i].red.x + BW) &&
            (chess[i].red.y < point.y()) && (point.y() < chess[i].red.y + BH))
            return i;
        else if ((chess[i].black.x < point.x()) && (point.x() < chess[i].black.x + BW) &&
                 (chess[i].black.y < point.y()) && (point.y() < chess[i].black.y + BH))
                return (i + CASENUM);
    }
    return -1;
}

void NimField::paintEvent( QPaintEvent *e )
{
    //QRect updateR = e->rect();
    QPainter p( this );

	//DrawChessman(e,iCurSelCol);
	int        i;
	p.setPen(black);
	for (i = 0;i < 18;i++)//18??
    {
        if (i < 9)//??(??)
        {
            p.moveTo(HX1,HY1 + BH * i) ;
            p.lineTo(HX1 + BW * CASENUM,HY1 + BH * i) ;
        }
        else//??(??)
        {
            p.moveTo(HX1 + BW * (i - 9),HY1) ;
            p.lineTo(HX1 + BW * (i - 9),HY1 + BH * CASENUM) ;
        }
    }

	p.setBrush(red);
	p.setPen(NoPen);

    for (i = 0;i < CASENUM;i++)//?????
	    p.drawPie(QRect(chess[i].red.x,chess[i].red.y,BW,BH),0,360 * 16);

	p.setBrush(black);
	p.setPen(NoPen);

    for (i = 0;i < CASENUM;i++)//?????
	    p.drawPie(QRect(chess[i].black.x,chess[i].black.y,BW,BH),0,360 * 16);
	/////////////////////////////////////////
	p.setBrush(black);
	p.setPen(NoPen);
	QPointArray point(1);
	point[0] = QPoint(HX1 + BW * iCurSelCol + BW / 2,HY1 + BH * CASENUM + 1);
	point.putPoints(1,2,HX1 + BW * iCurSelCol,HY1 + BH * (CASENUM + 1),
	                HX1 + BW * (iCurSelCol + 1),HY1 + BH * (CASENUM + 1));

	p.drawPolygon(point);

	if (qClew != "")//if (IfGameOver())
	{
	    p.setPen(black);
		p.setFont(QFont("Courier",48,QFont::Bold));
		p.drawText(rect(),AlignBottom,qClew);
	}
	if (qPrompt != "")
	{
        p.setPen(black);
		p.setFont(QFont("Courier",12,QFont::Bold));
		p.drawText(rect(),AlignBottom,qPrompt);
	}
}

/*********************************************************************\
* Function       InitChessman
* Purpose     ???????,????
* Params
* Return
* Remarks
**********************************************************************/
void NimField::InitChessman()
{
    int i,ired = 0,iblack = 0;
	//QRect r(0,0,1000,1000);

	srand((unsigned)time(NULL));
	for (i = 0;i < CASENUM;i++)
    {
	    ired                   = rand() % 4;
        iblack                 = rand() % 4 + 4;

        chess[i].red.x         = HX1 + BW * i;
        chess[i].red.y         = HY1 + BH * ired;
        chess[i].black.x       = HX1 + BW * i;
        chess[i].black.y       = HY1 + BH * iblack;

        chess[i].redbak.x      = chess[i].red.x;
		chess[i].redbak.y      = chess[i].red.y;
        chess[i].redregret.x   = chess[i].red.x;
		chess[i].redregret.y   = chess[i].red.y;
        chess[i].blackbak.x    = chess[i].black.x;
		chess[i].blackbak.y    = chess[i].black.y;
        chess[i].blackregret.x = chess[i].black.x;
		chess[i].blackregret.y = chess[i].black.y;
    }
    repaint();//repaint(0,0,1000,1000,TRUE);
	//emit
}
