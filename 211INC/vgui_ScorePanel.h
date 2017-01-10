
#ifndef SCOREPANEL_H
#define SCOREPANEL_H

#include<VGUI_Panel.h>
#include<VGUI_TablePanel.h>
#include<VGUI_HeaderPanel.h>
#include<VGUI_TextGrid.h>
#include<VGUI_Label.h>

#define MAX_SCORES 10

// Scoreboard cells
#define NUM_COLUMNS				5
#define NUM_ROWS				(MAX_PLAYERS + MAX_TEAMS)

// Scoreboard positions
#define SBOARD_INDENT_X			XRES(104)
#define SBOARD_INDENT_Y			YRES(40)

using namespace vgui;

//-----------------------------------------------------------------------------
// Purpose: Custom label for cells in the Scoreboard's Table Header
//-----------------------------------------------------------------------------
class CLabelHeader : public Label
{
private:
	void Init( void )
	{
		setFont( Scheme::sf_primary1 );
		setFgColor( Scheme::sc_primary1 );
		setBgColor( 0,0,0, 255 );
	}
public:

	CLabelHeader(const char* text,int x,int y,int wide,int tall) : Label(text,x,y,wide,tall)
	{
		Init();
	}

	CLabelHeader(const char* text, bool bAlignLeft = false) : Label(text)
	{
		Init();

		if (bAlignLeft)
			setContentAlignment(Label::a_west);
	}
};

//-----------------------------------------------------------------------------
// Purpose: Custom Table for the scoreboard
//-----------------------------------------------------------------------------
class ScoreTablePanel : public TablePanel
{
private:
	TextGrid	*_textGrid;
	Label		*m_pLabel;

public:
	int		m_iRows;
	int		m_iSortedRows[NUM_ROWS];
	int		m_iIsATeam[NUM_ROWS];
	bool	m_bHasBeenSorted[MAX_PLAYERS];
	int		m_iLastKilledBy;
	int		m_fLastKillTime;

public:
	ScoreTablePanel(int x,int y,int wide,int tall,int columnCount) : TablePanel(x,y,wide,tall,columnCount)
	{
		setCellEditingEnabled(false);
		
		m_pLabel = new Label( "", 0, 0, wide, tall );
		m_pLabel->setFont( Scheme::sf_primary2 );
	}
	virtual int getRowCount()
	{
		return m_iRows;
	}
	virtual Panel* startCellEditing(int column,int row)
	{
		return null;
	}
	virtual Panel* getCellRenderer(int column,int row,bool columnSelected,bool rowSelected,bool cellSelected);
	virtual int getCellTall(int row);
};

//-----------------------------------------------------------------------------
// Purpose: Scoreboard back panel
//-----------------------------------------------------------------------------
class ScorePanel : public Panel
{
private:
	HeaderPanel		*_headerPanel;
	ScoreTablePanel *_tablePanel;
	Label			*m_pTitleLabel;

public:
	int m_iNumTeams;
	int m_iPlayerNum;
	int m_iShowscoresHeld;

public:
	ScorePanel(int x,int y,int wide,int tall);
	virtual void setSize(int wide,int tall);

	void Update( void );
	void SortTeams( void );
	void SortPlayers( int iTeam, char *team );
	void RebuildTeams( void );
	void DeathMsg( int killer, int victim );

	void Initialize( void );

	void Open( void )
	{
		RebuildTeams();
		setVisible(true);
	}
};

#endif