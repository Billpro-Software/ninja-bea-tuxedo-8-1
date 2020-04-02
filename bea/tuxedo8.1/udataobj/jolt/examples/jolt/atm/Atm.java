/*
 * This ATM source is for demo purpose.  The software is provided "as is"
 * without warranty of any kind including without limitation, any warranty
 * of merchant ability or fitness for a particular purpose.  Further, BEA
 * Systems does not warrant, guarantee, or make any representations regarding
 * the use, or the results of the use, of the the software or written material
 * in terms of correctness, accuracy, reliability, or otherwise.
 *
 *
 * Copyright 1996-97 BEA Systems, Inc.  All Rights Reserved.
 */

package examples.jolt.atm;

import java.awt.*;
import java.io.*;
import java.util.Date;
import java.util.Random;
import java.util.Hashtable;
import java.util.StringTokenizer;
import java.util.NoSuchElementException;
import java.applet.Applet;
import java.applet.AudioClip;
import java.awt.image.ImageObserver;
import java.net.URL;
import bea.jolt.*;

/*
 * The ATM applet
 */
public class Atm extends Applet implements Runnable
{
    final static int	WELCOME_STATE = 0;
    final static int	SELECT_STATE = 1;
    final static int	INQUIRY_STATE = 2;
    final static int	INQUIRY_CHK_STATE = 3;
    final static int	INQUIRY_SAV_STATE = 4;
    final static int	DEPOSIT_STATE = 5;
    final static int	DEPOSIT_CHK_STATE = 6;
    final static int	DEPOSIT_SAV_STATE = 7;
    final static int	WITHDRAWAL_STATE = 8;
    final static int	WITHDRAWAL_CHK_STATE = 9;
    final static int	WITHDRAWAL_SAV_STATE = 10;
    final static int	TRANSFER_STATE = 11;
    final static int	TRANSFER_CHK_SAV_STATE = 12;
    final static int	TRANSFER_SAV_CHK_STATE = 13;
    final static int	NEXT_CMD_STATE = 14;
    final static String	INQUIRY = "Inquiry";
    final static String	WITHDRAWAL = "Withdrawal";
    final static String	DEPOSIT = "Deposit";
    final static String	TRANSFER = "Transfer";
    final static String	CHECKINGACCT = "Checking Acct";
    final static String	SAVINGACCT = "Saving Acct";
    final static String	CHECKING2SAVING = "Checking to Saving";
    final static String	SAVING2CHECKING = "Saving to Checking";
    final static String	X20 = "20", X40 = "40", X60 = "60";
    final static String	X80 = "80", X100 = "100", X120 = "120";
    final static String	X140 = "140", X160 = "160", X180 = "180";
    final static String	X200 = "200", X260 = "260", X300 = "300";
    final static int	verticalMargin = 40;
    final static int	horizontalMargin = 50;
    Panel		atmForeground;
    Panel		atmLeftPad;
    Image		leftArrow, rightArrow,
			beaLogo,	// the BEA image on the screen
			surround;	// the surround for the whole ATM
    AudioClip		audioDot, audioWrong, audioHelp;
    AtmServices		AtmServices;
    AtmScreen		atmScreen;
    AtmStatus		atmStatus;
    AtmClock		atmClock;
    Thread		clock;
    Thread		scrollTxt;
    int			state;
    String		msg[];
    String		pin;
    String		amount;
    String		status;
    String		transStatus;
    int			checkingAcct;
    int			savingAcct;
    Hashtable		pinHash;

    private void setUpAccounts()
    {
	int npins = Integer.parseInt(getParameter("numpins"));
	pinHash = new Hashtable(npins);
	for (int i = 0; i < npins; i++)
	{
		String val = getParameter("pin"+i);
		if (val == null)
			continue;

		StringTokenizer tokens = new StringTokenizer(val, ",");
		try
		{
			String pin = tokens.nextToken();

			/* Checking account and saving account */
			int accounts[] = new int[2];
			accounts[0] = Integer.parseInt(tokens.nextToken());
			accounts[1] = Integer.parseInt(tokens.nextToken());
			pinHash.put(pin, accounts);
		}
		catch (NoSuchElementException e)
		{
			System.err.println("Invalid Pin/Account format: "+val);
		}
		catch (NumberFormatException e)
		{
			System.err.println("Invalid Pin/Account number: "+val);
		}
	}
    }

    // Verify PIN and get the account numbers.  This function should be part
    // of the Tuxedo TLR Service
    boolean getAcctNum(String pin)
    {
	int accounts[] = (int []) pinHash.get(pin);
	if (accounts == null)
		return false;
	checkingAcct = accounts[0];
	savingAcct = accounts[1];
	return true;
    }

    public void addPIN(String digit)
    {
	pin += digit;
    }

    public void clearPIN()
    {
	pin = "";
    }

    public String getPIN()
    {
	return pin;
    }

    public void addAmount(String digit)
    {
	amount += digit;
    }

    public void setTransStatus(String s)
    {
	transStatus = s;
    }

    public void setAmount(String amnt)
    {
	amount = amnt;
    }

    public void clearAmount()
    {
	amount = "";
    }

    public String getAmount()
    {
	return amount;
    }

    public void close()
    {
	setStatus("Closed");
    	setStateMsg(WELCOME_STATE);
    }

    public void paint(Graphics g)
    {
	Dimension d = getSize();
	Insets borders = getInsets();
	int client_width = d.width - borders.right - borders.left;
	int client_height = d.height - borders.bottom - borders.top;
	int image_width = surround.getWidth(this);
	int image_height = surround.getHeight(this);

	g.drawImage(surround, 0, 0, this);
	int countx = client_width / image_width;
	int county = client_height / image_height;
	for( int i = 0; i <= countx; i++ )
	{
	    for( int j = 0; j <= county; j++ )
	    {
		if( i+j > 0 )
		{
		    g.drawImage(surround, i * image_width,
				j * image_height, this);
		}
	    }
	}
    }
		    
    public void init()
    {
    	MediaTracker	tracker;
	/* Changed to getCodeBase() from getDocBase() so 
	   we can use the jar file
	*/
	URL		dbase = getCodeBase(); 

	leftArrow = getImage(dbase, "images/left.gif");
	rightArrow = getImage(dbase, "images/right.gif");
	beaLogo = getImage(dbase, "images/beaLogo.gif");
	surround = getImage(dbase, "images/surround.gif");
	audioDot = getAudioClip(dbase, "audio/dot.au");
	audioWrong = getAudioClip(dbase, "audio/splat.au");
	audioHelp = getAudioClip(dbase, "audio/ring.au");

	tracker = new MediaTracker(this);
	tracker.addImage(leftArrow, 1);
	tracker.addImage(rightArrow, 2);
	tracker.addImage(beaLogo, 3);
	try
	{
		tracker.waitForAll();
	}
	catch (InterruptedException e) { }

	clearPIN();
	clearAmount();
	msg = new String[13];

	atmForeground = new Panel();
	atmForeground.setLayout(new BorderLayout());

	createKeyPadPanel();
	atmScreen = new AtmScreen(this, leftArrow, rightArrow, beaLogo);

	atmForeground.add("West", atmLeftPad);
	atmForeground.add("Center", atmScreen);

	Dimension bgSize = getSize();
	Insets borders = getInsets();
	
	setLayout(null);
	int bricksWidth = bgSize.width - borders.left - borders.right;
	int bricksHeight = bgSize.height - borders.top - borders.bottom;
	int atmForegroundWidth = bricksWidth - 2 * horizontalMargin;
	int atmForegroundHeight = bricksHeight - 2 * verticalMargin;
	int atmForegroundX = horizontalMargin + borders.left;
	int atmForegroundY = verticalMargin + borders.top;
	atmForeground.setBounds(atmForegroundX, atmForegroundY,
			      atmForegroundWidth, atmForegroundHeight);
	add(atmForeground);

	// Hook up to Tuxedo
	int	port = Integer.parseInt(getParameter("port"));
	String	svr = get_default_server();
	if ((svr == null) || (svr.length() == 0))
		svr = getParameter("host");
	setUpAccounts();

	AtmServices = new AtmServices(this);
	AtmServices.init(svr, port);

	setStateMsg(WELCOME_STATE);
    }

    String get_default_server()
    {
	URL	u = getDocumentBase();
	return u.getHost();
    }

    public void start()
    {
	clock = new Thread(this);
	clock.setPriority(6);
	clock.start();

	if (getState() == WELCOME_STATE)
	{
		scrollTxt = new Thread(this);
		scrollTxt.start();
	}
    }

    public void stop()
    {
	// Iconified will kill the clock thread and the scrollTxt thread.
	if (clock != null)
	{
		clock.stop();
		clock = null;
	}
	if (scrollTxt != null)
	{
		scrollTxt.stop();
		scrollTxt = null;
	}
	// On Win95, this gives a chance to another threads a chance to
	// stop and wo not be locked up.
	Thread.yield();
    }

    public void destroy()
    {
	AtmServices.destroy();
    }

    public void run()
    {
	Thread	me = Thread.currentThread();

	if ((clock != null) && (me == clock))
	{
		while (clock != null)
		{
			try
			{
				String	date = (new Date()).toString();

				byte[] time = date.getBytes();
				date = new String(time, 11, 8);
				atmClock.setTime(date);
				clock.sleep(1000);
			}
			catch (InterruptedException e)
			{
				// Do nothing.
			}
		}
	}
	else if ((scrollTxt != null) && (me == scrollTxt))
	{
		int	i;
		int	y = 240;		// starting at right
		Image	beaImage = createImage(y, 40);
		Graphics beaGC = beaImage.getGraphics();
		Random	random = new Random();
		String	msg[] = { "Tuxedo", "Java", "Internet", "Jolt", "BEA" };
		int	len[] = new int[msg.length];

		beaGC.setFont(new Font("TimesRoman", Font.BOLD, 36));
		FontMetrics fm = beaGC.getFontMetrics();
		for (i = 0; i < msg.length; i++)
			len[i] = -(fm.stringWidth(msg[i]));
		i = 0;
		while ((scrollTxt != null) && (me == scrollTxt))
		{
			try
			{
				beaGC.setColor(Color.black);
				beaGC.fillRect(0, 0, 240, 40);
				beaGC.setColor(Color.yellow);
				beaGC.drawString(msg[i], y -= 10, 38);
				atmScreen.paintScrollTxt(beaImage);

				// The message scrolls off the screen, choose
				// another one.
				if (y < len[i])
				{
					y = 240;
					i = ((random.nextInt() & 0xff0)>>4) %
						msg.length;
				}

				// 1/10 sec motion.
				scrollTxt.sleep(100);
			}
			catch (InterruptedException e)
			{
				// Do nothing.
			}
		}
	}
    }

    void createKeyPadPanel()
    {
	String	labels[] = {
		"1", "2", "3", "Change",
		"4", "5", "6", "Cancel",
		"7", "8", "9", "Help",
		" ", "0", ".", "OK"
	};
	Color	colors[] = {
		Color.white, Color.white, Color.white, Color.yellow,
		Color.white, Color.white, Color.white, Color.red,
		Color.white, Color.white, Color.white, new Color(180, 180, 255),
		Color.white, Color.white, Color.white, new Color(68, 187, 85)
	};
	Font	sfont = new Font("TimesRoman", Font.BOLD, 12);
	Font	lfont = new Font("TimesRoman", Font.BOLD, 18);
	Font	fonts[] = {
		lfont, lfont, lfont, sfont,
		lfont, lfont, lfont, sfont,
		lfont, lfont, lfont, sfont,
		lfont, lfont, lfont, sfont
	};

	atmLeftPad = new Panel();
	atmLeftPad.setLayout(new BorderLayout());

	Panel atmBottomPad = new Panel();
	atmBottomPad.setLayout(new FlowLayout(FlowLayout.LEFT));
	atmClock = new AtmClock(this, 108, 40);
	atmStatus = new AtmStatus(this, 108, 40);
	atmBottomPad.add(atmClock);
	atmBottomPad.add(atmStatus);

	// Add the keypad panel
	Panel atmKeyPad = new Panel();
	atmKeyPad.setLayout(new GridLayout(4, 4));

	// Add the keypads
	for (int i = 0 ; i < labels.length; i++)
	{
		AtmButton	keyPad;
		keyPad = new AtmButton(this, labels[i], colors[i], fonts[i]);
		if (labels[i].equals(" "))
			keyPad.setEnabled(false);
		atmKeyPad.add(keyPad);
	}

	atmLeftPad.add("Center", atmKeyPad);
	atmLeftPad.add("South", atmBottomPad);
    }

    public void setStatus(String string)
    {
	status = string;
	atmStatus.repaint();
    }

    public String getStatus()
    {
	return status;
    }

    public void setMsg(int lineno, String s)
    {
	msg[lineno] = s;
	atmScreen.paintMsgArea(lineno, s);
    }

    public String [] getMsg()
    {
	return msg;
    }

    public void clrMsg()
    {
	for (int i = 0; i < msg.length; i++)
		msg[i] = "";
	atmScreen.clrLabels();
	atmScreen.paintMsgArea(msg);
    }

    // Assign the labels for ATM arrows buttons.  The labels are left and
    // right justified.  So, it looks like: "left      right"
    public void assignLabel(int num, String left, String right)
    {
	Graphics	g = atmScreen.getGraphics();
	FontMetrics	fm = g.getFontMetrics();
	int		nSpace = (245 - fm.stringWidth(left) -
				  fm.stringWidth(right)) / fm.charWidth(' ');
	char		blanks[] = new char[nSpace];

	while (--nSpace >= 0)
		blanks[nSpace] = ' ';
	msg[(num + 2) * 2] = left + blanks + right;
	atmScreen.setLabel(num * 2, left);
	atmScreen.setLabel(num * 2 + 1, right);
    }

    public int getState()
    {
	return state;
    }

    void setStateMsg(int state)
    {
	// It is a hack!  State 14 is to wait for OK after a transaction.
	this.state = state;
	if (state != NEXT_CMD_STATE)
	{
		for (int i = 0; i < msg.length; i++)
			msg[i] = "";
		atmScreen.clrLabels();
	}

	switch (state)
	{
	case WELCOME_STATE:
		msg[0] = "      Welcome to Bank of BEA";
		if (status.equals("Open"))
			msg[2] = "      Please Enter your PIN.";
		else
			msg[2] = "      Please come back later.";
		break;
	case SELECT_STATE:
		msg[0] = "Please Select a Transaction";
		assignLabel(0, INQUIRY, TRANSFER);
		assignLabel(1, DEPOSIT, WITHDRAWAL);
		break;
	case INQUIRY_STATE:
		msg[0] = "Select Account for Inquiry";
		assignLabel(0, CHECKINGACCT, SAVINGACCT);
		break;
	case DEPOSIT_STATE:
		msg[0] = "Select Account for Deposit";
		assignLabel(0, CHECKINGACCT, SAVINGACCT);
		break;
	case DEPOSIT_CHK_STATE:
	case DEPOSIT_SAV_STATE:
		msg[0] = "Enter the Deposit Amount";
		msg[1] = "$ " + amount;
		break;
	case WITHDRAWAL_STATE:
		msg[0] = "Select Account for Withdrawal";
		assignLabel(0, CHECKINGACCT, SAVINGACCT);
		break;
	case WITHDRAWAL_CHK_STATE:
	case WITHDRAWAL_SAV_STATE:
		msg[0] = "Select a Withdrawal Amount";
		msg[1] = "$ ";
		assignLabel(0, X20, X40);
		assignLabel(1, X60, X80);
		assignLabel(2, X100, X120);
		assignLabel(3, X140, X160);
		assignLabel(4, X200, X300);
		break;
	case TRANSFER_STATE:
		msg[0] = "Select a Type of Transfer";
		assignLabel(0, CHECKING2SAVING, "");
		assignLabel(1, SAVING2CHECKING, "");
		break;
	case TRANSFER_CHK_SAV_STATE:
	case TRANSFER_SAV_CHK_STATE:
		msg[0] = "Enter the Transfer Amount";
		msg[1] = "$ ";
		break;
	case NEXT_CMD_STATE:	// Wait for OK after a transaction.
		break;
	}

	if (state != NEXT_CMD_STATE)
		atmScreen.paintMsgArea(msg);

	if (state == WELCOME_STATE)
		atmScreen.showLogo (true);
	else
		atmScreen.showLogo (false);
    }

    void savingBalHdr()
    {
	clrMsg();
	setMsg(0, "Balance in Saving Acct");
	setMsg(1, "One Moment...");
	setMsg(2, "");
    }

    void checkingBalHdr()
    {
	clrMsg();
	setMsg(0, "Balance in Checking Acct");
	setMsg(1, "One Moment...");
	setMsg(2, "");
    }

    // This is the actual ATM state machine
    public void changeState( String s )
    {
	if (s.equals("OK"))
	{
		try
		{
			audioDot.play();
		}
		catch (Exception e) { }

		try
		{
			transStatus="";
			switch (getState())
			{
			case WELCOME_STATE:
				if (getAcctNum(getPIN()) == false)
				{
					clearPIN();
					audioWrong.play();
					return;
				}
				clearAmount();
				scrollTxt = null;
				setStateMsg(SELECT_STATE);
				break;
			case DEPOSIT_CHK_STATE:
				checkingBalHdr();
				AtmServices.deposit(checkingAcct, amount);
				setMsg(1, amount);
				setMsg(2, transStatus);
				setStateMsg(NEXT_CMD_STATE);
				break;
			case DEPOSIT_SAV_STATE:
				savingBalHdr();
				AtmServices.deposit(savingAcct, amount);
				setMsg(1, amount);
				setMsg(2, transStatus);
				setStateMsg(NEXT_CMD_STATE);
				break;
			case WITHDRAWAL_CHK_STATE:
				checkingBalHdr();
				AtmServices.withdrawal(checkingAcct, amount);
				setMsg(1, amount);
				setMsg(2, transStatus);
				setStateMsg(NEXT_CMD_STATE);
				break;
			case WITHDRAWAL_SAV_STATE:
				savingBalHdr();
				AtmServices.withdrawal(savingAcct, amount);
				setMsg(1, amount);
				setMsg(2, transStatus);
				setStateMsg(NEXT_CMD_STATE);
				break;
			case TRANSFER_CHK_SAV_STATE:
				clrMsg();
				setMsg(0, "One Moment...");
				setMsg(1, "");
				AtmServices.transfer(checkingAcct, savingAcct,
						amount);
				setMsg(0, "Balance in Checking: " + msg[0]);
				setMsg(1, "Balance in Saving:   " + msg[1]);
				setMsg(2, transStatus);
				setStateMsg(NEXT_CMD_STATE);
				break;
			case TRANSFER_SAV_CHK_STATE:
				clrMsg();
				setMsg(0, "One Moment...");
				setMsg(1, "");
				AtmServices.transfer(savingAcct, checkingAcct,
							amount);
				setMsg(0, "Balance in Saving:   " + msg[0]);
				setMsg(1, "Balance in Checking: " + msg[1]);
				setMsg(2, transStatus);
				setStateMsg(NEXT_CMD_STATE);
				break;
			case NEXT_CMD_STATE:
				setStateMsg(SELECT_STATE);
				clearAmount();
				break;
			}
		}
		catch (IOException e)
		{
			// AtmServices failed!
			return;
		}
		catch (Exception e)
		{
			// Audio failed!
		}
	}
	else if (s.equals("Cancel"))
	{
		try
		{
			audioDot.play();
		}
		catch (Exception e) { }

		if (getState() == WELCOME_STATE)
			clearPIN();
		else if (getState() == SELECT_STATE)
		{
			clearPIN();
			setStateMsg(WELCOME_STATE);
			if (scrollTxt != null)
				scrollTxt.resume();
			else
			{
				scrollTxt = new Thread(this);
				scrollTxt.start();
			}
		}
		else
		{
			setStateMsg(SELECT_STATE);
			clearAmount();
		}
	}
	else if (s.equals("Change"))
	{
		try
		{
			audioDot.play();
		}
		catch (Exception e) { }

		switch (getState())
		{
		case WELCOME_STATE:
			clearPIN();
			break;
		case DEPOSIT_CHK_STATE:
		case DEPOSIT_SAV_STATE:
		case WITHDRAWAL_CHK_STATE:
		case WITHDRAWAL_SAV_STATE:
		case TRANSFER_CHK_SAV_STATE:
		case TRANSFER_SAV_CHK_STATE:
			clearAmount();
			msg[1] = "$ ";
			atmScreen.paintMsgArea(1, msg[1]);
			break;
		}
	}
	else if (s.equals("Help"))
	{
		try
		{
			audioHelp.play();
		}
		catch (Exception e) { }
	}
	else if (s.equals(INQUIRY))
		setStateMsg(INQUIRY_STATE);
	else if (s.equals(TRANSFER))
		setStateMsg(TRANSFER_STATE);
	else if (s.equals(DEPOSIT))
		setStateMsg(DEPOSIT_STATE);
	else if (s.equals(WITHDRAWAL))
		setStateMsg(WITHDRAWAL_STATE);
	else if (s.equals(CHECKING2SAVING))
		setStateMsg(TRANSFER_CHK_SAV_STATE);
	else if (s.equals(SAVING2CHECKING))
		setStateMsg(TRANSFER_SAV_CHK_STATE);
	else if (s.equals(CHECKINGACCT))
	{
		switch (getState())
		{
		case INQUIRY_STATE:
			checkingBalHdr();
			try
			{
				AtmServices.inquiry(checkingAcct);
				setMsg(1, amount);
				setMsg(2, transStatus);
				setStateMsg(NEXT_CMD_STATE);
			}
			catch (IOException e)
			{
				return;
			}
			break;
		case DEPOSIT_STATE:
			setStateMsg(DEPOSIT_CHK_STATE);
			break;
		case WITHDRAWAL_STATE:
			setStateMsg(WITHDRAWAL_CHK_STATE);
			break;
		}
	}
	else if (s.equals(SAVINGACCT))
	{
		switch (getState())
		{
		case INQUIRY_STATE:
			savingBalHdr();
			try
			{
				AtmServices.inquiry(savingAcct);
				setMsg(1, amount);
				setMsg(2, transStatus);
				setStateMsg(NEXT_CMD_STATE);
			}
			catch (IOException e)
			{
				return;
			}
			break;
		case DEPOSIT_STATE:
			setStateMsg(DEPOSIT_SAV_STATE);
			break;
		case WITHDRAWAL_STATE:
			setStateMsg(WITHDRAWAL_SAV_STATE);
			break;
		}
	}
	else if (s.equals(X20) || s.equals(X40) || s.equals(X60) ||
		 s.equals(X80) || s.equals(X100) || s.equals(X120) ||
		 s.equals(X140) || s.equals(X160) || s.equals(X200) ||
		 s.equals(X300))
	{
		amount = s;
		msg[1] = "$ " + amount + ".00";
		atmScreen.paintMsgArea(1, msg[1]);
	}
	else if (s.equals(""))
	{
		// Do nothing
	}
	else
	{
		try
		{
			audioDot.play();
		}
		catch (Exception e) { }

		switch (getState())
		{
		case WELCOME_STATE:
			addPIN(s);
			break;
		case DEPOSIT_CHK_STATE:
		case DEPOSIT_SAV_STATE:
		case WITHDRAWAL_CHK_STATE:
		case WITHDRAWAL_SAV_STATE:
		case TRANSFER_CHK_SAV_STATE:
		case TRANSFER_SAV_CHK_STATE:
			addAmount(s);
			msg[1] = "$ " + amount;
			atmScreen.paintMsgArea(1, msg[1]);
			break;
		}
	}
    }
}

/*
 * The Left or Right Arrow Button in the ATM Screen.
 */
class AtmArrow
{
    Image	arrow;
    Rectangle	rec;
    String	label;

    public AtmArrow(Image arrow, int x, int y, int w, int h)
    {
	this.arrow = arrow;
	rec = new Rectangle(x, y, w, h);
    }

    public void paint(Graphics g, ImageObserver obs)
    {
	g.drawImage(arrow, rec.x, rec.y, obs);
    }

    public boolean contains(int x, int y)
    {
	return rec.contains(x, y);
    }

    public void setLabel(String s)
    {
	label = s;
    }

    public String getLabel()
    {
	return label;
    }
}

class AtmCenterTextCanvas extends Canvas
{
    void drawCenteredText(Graphics g, String s, Color c, Dimension r)
    {
	FontMetrics	fm = g.getFontMetrics();
	int		width = (r.width - fm.stringWidth(s)) / 2;
	int		height = (r.height + fm.getHeight()) / 2;

	g.setColor(c);
	g.drawString(s, width, height);
    }
}

/*
 * Canvas for the real-time clock.
 */
class AtmClock extends AtmCenterTextCanvas
{
    Atm		atm;
    int		width;
    int		height;
    Image	clockImage;
    Graphics	clockGC;
    FontMetrics	clockFM;

    public AtmClock( Atm atm, int width, int height )
    {
	this.atm = atm;
	clockImage = null;
	this.width = width;
	this.height = height;
	setSize(width, height);
    }

    public void paint(Graphics g)
    {
	if (clockImage != null)
		g.drawImage(clockImage, 0, 0, this);
    }


    public void setTime(String tod)
    {
	if (clockImage == null)
	{
		clockImage = createImage(width, height);
		clockGC = clockImage.getGraphics();
		clockGC.setFont(new Font("TimesRoman", Font.BOLD, 16));
	}
	clockGC.setColor(getBackground());
	clockGC.fillRect(0, 0, width, height);
	clockGC.setColor(getForeground());
	drawCenteredText(clockGC, tod, getForeground(), getSize());
	repaint();
    }
}

/*
 * ATM Status: Open or Close (any transaction failure).
 */
class AtmStatus extends AtmCenterTextCanvas
{
    Atm		atm;
    Image	statusImage;
    Graphics	statusGC;

    public AtmStatus( Atm atm, int width, int height )
    {
	this.atm = atm;
	statusImage = null;
	statusGC = null;
	setBounds(0, 0, width, height);
    }

    public void paint(Graphics g)
    {
	Dimension s = getSize();
	int	x = (s.width - 80) / 2;
	int	y = (s.height - 32) / 2;
	String	status = atm.getStatus();

	if (statusImage == null)
	{
		statusImage = createImage(s.width, s.height);
		statusGC = statusImage.getGraphics();
		statusGC.setFont(new Font("TimesRoman", Font.BOLD, 16));
	}

	// Pale green box for "Open" or Red for "Close".
	statusGC.setColor(getBackground());
	statusGC.fillRect(0, 0, s.width, s.height);
	if (status.equals("Open"))
		draw3DBox(statusGC, x, y, 80, 32, new Color(68, 187, 85));
	else
		draw3DBox(statusGC, x, y, 80, 32, Color.red);

	drawCenteredText(statusGC, status, Color.white, s);
	g.drawImage(statusImage, 0, 0, this);
    }

    // draw3Drect() does not do what I want.  I need to write my own.
    void draw3DBox(Graphics g, int x, int y, int w, int h, Color color)
    {
	int	red = color.getRed();
	int	green = color.getGreen();
	int	blue = color.getBlue();

	// 16% darker for the broader
	red -= (red >> 3) + (red >> 5);
	green -= (green >> 3) + (green >> 5);
	blue -= (blue >> 3) + (blue >> 5);
	g.setColor(new Color(red, green, blue));
	g.drawLine(x, y, x + w, y);
	g.drawLine(x , y + 1, x + w, y + 1);
	g.drawLine(x, y, x, y + h);
	g.drawLine(x + 1, y, x + 1, y + h);
	g.setColor(Color.white);
	g.drawLine(x, y + h, x + w, y + h);
	g.drawLine(x + w, y + h, x + w, y);
	g.setColor(color);
	g.fillRect(x + 2, y + 2, w - 2, h - 2);
    }
}

/*
 * Screen for the ATM display.
 */
class AtmScreen extends Canvas
{
    AtmArrow	arrows[];
    Atm		atm;
    private boolean showlogo;
    private Image logo;

    public AtmScreen( Atm atm, Image leftArrow, Image rightArrow,
				Image beaLogo)
    {
	int	h = leftArrow.getHeight(atm);
	int	w = leftArrow.getWidth(atm);

	this.atm = atm;
	arrows = new AtmArrow[10];
	for (int i = 0; i < 10; i++)
	{
		if ((i & 1) == 0)
			arrows[i] = new AtmArrow(rightArrow, 10,
						93 + (i / 2) * 48, w, h);
		else
			arrows[i] = new AtmArrow(leftArrow, 300,
						93 + (i / 2) * 48, w, h);
	}

	// Set the font to match the text in msg area.  This font will be
	// used in Atm.AssignLabel().
	setFont(new Font("TimesRoman", Font.BOLD, 18));
	showlogo = true;
	logo = beaLogo;
    }

    public void paint(Graphics g)
    {
	// Set my background color
	g.setColor(Color.black);
	g.fillRect(0, 0, getSize().width, getSize().height);

	for (int i = 0; i < 10; i++)
		arrows[i].paint(g, this);

	// Write the message
	paintMsgArea(atm.getMsg());
	showLogo (showlogo);
    }

    void paintScrollTxt(Image scrollTxtImage)
    {
	Graphics g = getGraphics();
	g.drawImage(scrollTxtImage, 50, 130, atm);
    }

    void paintMsgArea(String msg[])
    {
	Graphics g = getGraphics();

	g.setColor(Color.black);
	// First 3 lines are special that may have long text
	g.fillRect(0, 0, getSize().width, 20 + 24 * 3);
	g.fillRect(50, 0, 250, 350);
	g.setColor(Color.white);
	g.setFont(new Font("TimesRoman", Font.BOLD, 18));

	for (int i = 0; i < msg.length; i++)
		g.drawString(msg[i], 50, 20 + 24 * i);
    }

    void paintMsgArea(int msgno, String msg)
    {
	int	width;
	Graphics g = getGraphics();
	int	y = 20 + 24 * msgno;

	g.setColor(Color.black);
	// First 3 lines are special that may have long text
	width = (msgno <= 3) ? getSize().width : 250;
	g.fillRect(50, y - 20, width, 24);
	g.setColor(Color.white);
	g.setFont(new Font("TimesRoman", Font.BOLD, 18));
	g.drawString(msg, 50, y);
    }

    public void setLabel(int buttonNum, String s)
    {
	arrows[buttonNum].setLabel(s);
    }

    public void clrLabels()
    {
	for (int i = 0; i < arrows.length; i++)
		arrows[i].setLabel("");
    }

    public boolean mouseUp(Event e, int x, int y )
    {
	for (int i = 0; i < 10; i++)
	{
		if (arrows[i].contains(x, y))
		{
			String label = arrows[i].getLabel();
			if (label != null)
				atm.changeState(label);
			return true;
		}
	}

	return false;
    }

	public void showLogo(boolean flag)
	{
		showlogo = flag;
		if (logo == null)
			return;
		Graphics g = getGraphics();
			if (showlogo == true)
		g.drawImage(logo, 50, 200, atm);
	}
}

/*
 * ATM key pads.
 */
class AtmButton extends Button
{
	Atm	atm;

	public AtmButton(Atm atm, String label, Color color, Font font)
	{
		this.atm = atm;

		setLabel(label);
		setBackground(color);
		setForeground(color.black);
		setFont(font);
	}

	public boolean action(Event e, Object arg)
	{
		atm.changeState(getLabel());
		return true;
	}
}

/*
 * ATM Services: Inquiry, Deposit, Withdrawal, and Transfer.
 * An IOException will be raised if the transaction failed and
 * it will cause the ATM status set to Close.
 */
class AtmServices
{
    Atm			atm;
    JoltSession		session;
    JoltRemoteService	inquiry;
    JoltRemoteService	deposit;
    JoltRemoteService	withdrawal;
    JoltRemoteService	transfer;

    public AtmServices(Atm atm)
    {
	this.atm = atm;
	atm.setStatus("Open");
    }

    public void init(String host, int port)
    {
	JoltSessionAttributes attr = new JoltSessionAttributes();
	try
	{
		attr.setString(attr.APPADDRESS, "//" + host + ":" + port);

		session = new JoltSession(attr, "", "ATM", "", "");
		inquiry = new JoltRemoteService("INQUIRY", session);
		deposit = new JoltRemoteService("DEPOSIT", session);
		withdrawal = new JoltRemoteService("WITHDRAWAL", session);
		transfer = new JoltRemoteService("TRANSFER", session);
	}
	catch (SessionException e)
	{
		System.err.println(e);
		atm.close();
	}
	catch (ServiceException e)
	{
		System.err.println(e);
		session = null;
		atm.close();
	}
    }

    public void destroy()
    {
	if (session != null)
	{
		session.endSession();
		session = null;
	}
    }

    public void deposit(int acct_number, String amount) throws IOException
    {
	try
	{
		deposit.setInt("ACCOUNT_ID", acct_number);
		deposit.setString("SAMOUNT", amount);
		deposit.call(null);
		atm.setAmount(deposit.getStringDef("SBALANCE", ""));
		/*
		if ("Close".equals(atm.getStatus()))
			atm.setStatus("Open");
		*/
	}
	catch (ApplicationException e)
	{
		atm.setTransStatus(deposit.getStringDef("STATLIN", ""));
	}
	catch (ServiceException e)
	{
		atm.close();
		throw new IOException();
	}
    }

    public void withdrawal(int acct_number, String amount) throws IOException
    {
	try
	{
		withdrawal.setInt("ACCOUNT_ID", acct_number);
		withdrawal.setString("SAMOUNT", amount);
		withdrawal.call(null);
		atm.setAmount(withdrawal.getStringDef("SBALANCE", ""));
	}
	catch (ApplicationException e)
	{
		atm.setTransStatus(withdrawal.getStringDef("STATLIN", ""));
	}
	catch (ServiceException e)
	{
		atm.close();
		throw new IOException();
	}
    }

    public void transfer(int from_acct, int to_acct, String amount)
							throws IOException
    {
	try
	{
		transfer.setIntItem("ACCOUNT_ID", 0, from_acct);
		transfer.setIntItem("ACCOUNT_ID", 1, to_acct);
		transfer.setString("SAMOUNT", amount);
		transfer.call(null);
		(atm.getMsg())[0] = transfer.getStringItemDef("SBALANCE",0,"");
		(atm.getMsg())[1] = transfer.getStringItemDef("SBALANCE",1,"");
		atm.setTransStatus(transfer.getStringDef("STATLIN", ""));
	}
	catch (ApplicationException e)
	{
		atm.setTransStatus(transfer.getStringDef("STATLIN", ""));
	}
	catch (ServiceException e)
	{
		atm.close();
		throw new IOException();
	}
    }

    public void inquiry(int acct_number) throws IOException
    {
	try
	{
		inquiry.setInt("ACCOUNT_ID", acct_number);
		inquiry.call(null);
		atm.setAmount(inquiry.getStringDef("SBALANCE", ""));
		atm.setTransStatus(inquiry.getStringDef("STATLIN", ""));
	}
	catch (ApplicationException e)
	{
		atm.setTransStatus(inquiry.getStringDef("STATLIN", ""));
	}
	catch (ServiceException e)
	{
		atm.close();
		throw new IOException();
	}
    }
}
