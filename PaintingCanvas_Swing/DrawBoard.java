/*
this is a small application for drawing..
About How to Use It, Please Refer To The Document for details...
The main menu is on the top for you to choose what to do.
you can change the color, line width, font on clicking the button on the top.
you can draw lines, ellipses, rectangulars, or words.
you can change the line width and line color for drawing lines, ellis or rects.
you can change the font or size of the words.
you can choose a shape to delete.
you can save what you have drawn.
you can also open a file that you have saved.
Enjoy yourself! Thank you!
 */
import javax.sound.sampled.Line;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.io.*;
import java.util.ArrayList;

//input words.. create an textArea, and when press enter, delete it.
public class DrawBoard extends JFrame
{
    private JFrame myFrame;
    private JPanel myPanel;
    private JToolBar myToolBar;
    private JLabel myLabel;
    private JTextField myText;
    private MenuBar myMenuBar;
    private Menu menuFile, menuAbout, menuEdit;
    private MenuItem menuFileOpen, menuFileSave, menuFileExit, menuAboutabout, menuEditLine, menuEditRect, menuEditElli, menuEditWord, menuEditChoose;
    private ArrayList<MyRectangular> rects = new ArrayList<MyRectangular>();
    private ArrayList<MyEllipse> ellis = new ArrayList<MyEllipse>();
    private ArrayList<MyLine> lines = new ArrayList<MyLine>();
    private ArrayList<MyWord> words = new ArrayList<MyWord>();
    private MyRectangular currentRect;
    private MyEllipse currentElli;
    private MyLine currentLine;
    private MyWord currentWord;
    private int type; //1:line, 2:rect, 3:ellipse, 4:words
    private int sx, sy, ex, ey;
    private int colorChoose[] = {255,0,0};
    private int colorDefault[] = {0,0,0};
    private String fontName = "Times New Roman";
    private int fontSize = 15, lineWidth = 4;
    private boolean fontBold = false, fontItalic = false;
    private boolean drawing = false, drawLine = true, drawRect = false, drawElli = false, drawWords = false, deletable = false;
    private boolean flagT = false;
    public void display()
    {
        myFrame = new JFrame();
        myPanel = new JPanel();
        myFrame.setTitle("Simple Canvas");
        myFrame.setBackground(new Color(255, 255, 255));
        myFrame.setSize(800, 700);
        myFrame.setLocation(300, 300);
        myFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        myText = new JTextField(13);
        myText.setBounds(200, 500, 100, 30);
        myText.setColumns(10);
        myText.setVisible(false);
        myText.addKeyListener(
                new KeyAdapter() {
                    @Override
                    public void keyPressed(KeyEvent e) {
                        super.keyPressed(e);
                        Graphics g = myPanel.getGraphics();
                        if(e.getKeyCode() == KeyEvent.VK_ENTER)
                        {
                            //myText.setVisible(false);
                            //myText.setOpaque(true);
                            drawAThing((Graphics2D) g);
                        }
                        //myText.setVisible(true);
                        //redrawAll((Graphics2D)g);
                    }
                }
        );
        myPanel.add(myText);

        //add panel
        //myPanel.setLayout(new BorderLayout());
        myFrame.setLayout(new BorderLayout());
        myPanel.setLayout(null);
        myPanel.addMouseListener(
                new MouseAdapter() {
                    @Override
                    public void mouseClicked(MouseEvent e) {
                        super.mousePressed(e);
                        Graphics g = myPanel.getGraphics();
                        if (deletable) {
                            boolean flag = find(e.getPoint());
                            if(flag) {
                                if (type == 1) {
                                    myLabel.setText("You can press 'delete' to delete this line");
                                    //lines.remove(currentLine);
                                } else if (type == 2) {
                                    myLabel.setText("You can press 'delete' to delete this rectangle");
                                    //rects.remove(currentRect);
                                } else if (type == 3) {
                                    myLabel.setText("You can press 'delete' to delete this ellipse");
                                    //ellis.remove(currentElli);
                                } else if (type == 4) {
                                    myLabel.setText("You can press 'delete' to delete this word");
                                }
                                redrawAll((Graphics2D) g);
                            }
                        } else {
                            if (drawWords) {
//                                myText.setVisible(false);
//                                redrawAll((Graphics2D) g);
                                sx = e.getX();
                                sy = e.getY();
                                myText.setBounds(sx - 5, sy - 12, 150, 40);
                                //myText.setLocation(e.getX(), e.getY());
                                myText.setVisible(true);
                                myText.setText("");
                                myText.requestFocus();
                                redrawAll((Graphics2D) g);
//                                myText.setVisible(false);
//                                redrawAll((Graphics2D) g);
                            }
                            else {
                                if (!drawing) {
                                    sx = e.getX();
                                    sy = e.getY();
                                    myLabel.setText("Please click to appoint a end point..");
                                } else {
                                    ex = e.getX();
                                    ey = e.getY();
                                    drawAThing((Graphics2D) g);
                                    myLabel.setText("Please click to appoint a start point..");
                                }
                                //System.out.println(sx + " " + sy);
                                drawing = !drawing;
                            }
                        }
                    }
                }
        );
        //for the text..
        myPanel.addMouseMotionListener(
                new MouseAdapter() {
                    @Override
                    public void mouseMoved(MouseEvent e) {
                        super.mouseMoved(e);
                        if(flagT){
                            Graphics g = myPanel.getGraphics();
                            redrawAll((Graphics2D) g);
                            flagT = false;
                        }
                        if(drawWords&&myText.isVisible()) {
                            Graphics g = myPanel.getGraphics();
                            myText.setVisible(false);
                            //redrawAll((Graphics2D) g);
                            flagT = true;
                        }
                        myFrame.requestFocus();
                    }
                });
        ///////
        myPanel.setBackground(new Color(255,255,255));
        myFrame.add(myPanel);
        myFrame.addKeyListener(
                new KeyAdapter() {
                    @Override
                    public void keyPressed(KeyEvent e) {
                        super.keyPressed(e);
                        Graphics g = myPanel.getGraphics();
                        if(deletable) {
                            if (e.getKeyCode() == KeyEvent.VK_DELETE || e.getKeyCode() == KeyEvent.VK_BACK_SPACE) {
                                if (type == 1) {
                                    myLabel.setText("delete line success! Continue selecting..");
                                    lines.remove(currentLine);
                                }
                                else if (type == 2) {
                                    myLabel.setText("delete rectangle success! Continue selecting..");
                                    rects.remove(currentRect);
                                }
                                else if (type == 3) {
                                    myLabel.setText("delete ellipse success! Continue selecting..");
                                    ellis.remove(currentElli);
                                }
                                else if (type == 4) {
                                    myLabel.setText("delete word success! Continue selecting..");
                                    //ellis.remove(currentElli);
                                    words.remove(currentWord);
                                }
                                redrawAll((Graphics2D) g);
                            }
                            //deletable = false;
                        }
                        //System.out.print("haha");
                    }
                }

        );
        //myFrame.pack();
        //add the menu bar
        myMenuBar = new MenuBar();
        menuFile = new Menu("FILE");
        menuEdit = new Menu("EDIT");
        menuAbout = new Menu("ABOUT");
        menuFileOpen = new MenuItem("open file");
        menuFileSave = new MenuItem("save file");
        menuFileExit = new MenuItem("exit");
        menuEditLine = new MenuItem("draw line");
        menuEditRect = new MenuItem("draw rectangle");
        menuEditElli = new MenuItem("draw ellipse");
        menuEditWord = new MenuItem("draw word");
        menuEditChoose = new MenuItem("choose a shape");
        menuAboutabout = new MenuItem("about");
        menuFileOpen.addActionListener(new MenuAction());
        menuFileSave.addActionListener(new MenuAction());
        menuFileExit.addActionListener(new MenuAction());
        menuEditLine.addActionListener(new MenuAction());
        menuEditRect.addActionListener(new MenuAction());
        menuEditElli.addActionListener(new MenuAction());
        menuEditWord.addActionListener(new MenuAction());
        menuEditChoose.addActionListener(new MenuAction());
        menuAboutabout.addActionListener(new MenuAction());
        menuFile.add(menuFileOpen);
        menuFile.add(menuFileSave);
        menuFile.add(menuFileExit);
        menuEdit.add(menuEditLine);
        menuEdit.add(menuEditRect);
        menuEdit.add(menuEditElli);
        menuEdit.add(menuEditWord);
        menuEdit.addSeparator();
        menuEdit.add(menuEditChoose);
        menuAbout.add(menuAboutabout);
        myMenuBar.add(menuFile);
        myMenuBar.add(menuEdit);
        myMenuBar.add(menuAbout);
        myFrame.setMenuBar(myMenuBar);

        JButton btn = new JButton("color, size and font");
        btn.setBounds(1, 1, 1, 1);
        btn.setVisible(true);
        btn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                ColorFontMessage message = new ColorFontMessage();
            }
        });
        myFrame.add(btn, BorderLayout.NORTH);

        myToolBar = new JToolBar();
        myToolBar.setFloatable(false);
        myToolBar.setBounds(0, 0, 100, 100);
        myLabel = new JLabel("Default: Draw Line, Please click to appoint the start point OR click EDIT menu to start drawing another shape");
        myToolBar.add(myLabel);
        myFrame.add(myToolBar, BorderLayout.SOUTH);
        myFrame.setResizable(false);
        myFrame.setVisible(true);

    }

    public boolean find(Point2D point)
    {
        int LINE_BOX_SIZE = 5;
        double BOX_X = point.getX() - LINE_BOX_SIZE / 2;
        double BOX_Y = point.getY() - LINE_BOX_SIZE / 2;
        for(MyLine l : lines)
        {
            if(l.getLine().intersects(BOX_X, BOX_Y, LINE_BOX_SIZE, LINE_BOX_SIZE))
            {
                type = 1;
                currentLine = l;
                return true;
            }
        }
        for(MyRectangular r : rects)
        {
            if(r.getRectangle().contains(point)||r.getRectangle().intersects(BOX_X, BOX_Y, LINE_BOX_SIZE, LINE_BOX_SIZE))
            {
                type = 2;
                currentRect = r;
                return true;
            }
        }
        for(MyEllipse e : ellis)
        {
            if(e.getEllipse().contains(point) || e.getEllipse().intersects(BOX_X, BOX_Y, LINE_BOX_SIZE, LINE_BOX_SIZE))
            {
                type = 3;
                currentElli = e;
                return true;
            }
        }
        for(MyWord w : words)
        {
            if(w.contains(point))
            {
                type = 4;
                currentWord = w;
                return true;
            }
        }
        return false;
    }

    // the handler for menu bar
    class MenuAction implements ActionListener {
        //JFrame myFrame;
        FileDialog fileDialog;
        //        MenuAction(JFrame f)
//        {
//            myFrame = f;
//        }
        @Override
        public void actionPerformed(ActionEvent e) {
            Graphics g = myPanel.getGraphics();
            if(e.getActionCommand().equals("open file"))
            {
                //System.out.println("open file");
                currentLine = null;
                currentElli = null;
                currentRect = null;
                currentWord = null;
                myLabel.setText("Now Opening File...");
                fileDialog = new FileDialog(myFrame, "open file", FileDialog.LOAD);
                fileDialog.setVisible(true);
                String fileName = fileDialog.getFile();
                String filePath = fileDialog.getDirectory();
                if(fileName!=null&&filePath!=null) {
                    try {
                        FileReader fr = new FileReader(filePath + fileName);
                        BufferedReader br = new BufferedReader(fr);
                        lines.clear();
                        rects.clear();
                        ellis.clear();
                        words.clear();
                        String s = br.readLine();
                        if (s.equals("lines begin")) {
                            s = br.readLine();
                            while (!s.equals("lines end")) {
                                int[] tmpRGB = new int[3];
                                tmpRGB[0] = Integer.parseInt(s);
                                s = br.readLine();
                                tmpRGB[1] = Integer.parseInt(s);
                                s = br.readLine();
                                tmpRGB[2] = Integer.parseInt(s);
                                int tmpX1, tmpY1, tmpX2, tmpY2;
                                s = br.readLine();
                                tmpX1 = Integer.parseInt(s);
                                s = br.readLine();
                                tmpY1 = Integer.parseInt(s);
                                s = br.readLine();
                                tmpX2 = Integer.parseInt(s);
                                s = br.readLine();
                                tmpY2 = Integer.parseInt(s);
                                int tmpStroke;
                                s = br.readLine();
                                tmpStroke = Integer.parseInt(s);
                                Line2D tmpLine = new Line2D.Double(tmpX1, tmpY1, tmpX2, tmpY2);
                                currentLine = new MyLine();
                                currentLine.setLine(tmpLine);
                                currentLine.setColor(tmpRGB);
                                currentLine.setStroke(tmpStroke);
                                lines.add(currentLine);
                                s = br.readLine();
                            }
                        }
                        s = br.readLine();
                        if (s.equals("rects begin")) {
                            s = br.readLine();
                            while (!s.equals("rects end")) {
                                int[] tmpRGB = new int[3];
                                tmpRGB[0] = Integer.parseInt(s);
                                s = br.readLine();
                                tmpRGB[1] = Integer.parseInt(s);
                                s = br.readLine();
                                tmpRGB[2] = Integer.parseInt(s);
                                int tmpX1, tmpY1, tmpX2, tmpY2;
                                s = br.readLine();
                                tmpX1 = Integer.parseInt(s);
                                s = br.readLine();
                                tmpY1 = Integer.parseInt(s);
                                s = br.readLine();
                                tmpX2 = Integer.parseInt(s);
                                s = br.readLine();
                                tmpY2 = Integer.parseInt(s);
                                int tmpStroke;
                                s = br.readLine();
                                tmpStroke = Integer.parseInt(s);
                                Rectangle2D tmpRect = new Rectangle2D.Double(tmpX1, tmpY1, tmpX2 - tmpX1, tmpY2 - tmpY1);
                                currentRect = new MyRectangular();
                                currentRect.setRectangle(tmpRect);
                                currentRect.setColor(tmpRGB);
                                currentRect.setStroke(tmpStroke);
                                rects.add(currentRect);
                                s = br.readLine();
                            }
                        }
                        s = br.readLine();
                        if (s.equals("ellis begin")) {
                            s = br.readLine();
                            while (!s.equals("ellis end")) {
                                int[] tmpRGB = new int[3];
                                tmpRGB[0] = Integer.parseInt(s);
                                s = br.readLine();
                                tmpRGB[1] = Integer.parseInt(s);
                                s = br.readLine();
                                tmpRGB[2] = Integer.parseInt(s);
                                int tmpX1, tmpY1, tmpX2, tmpY2;
                                s = br.readLine();
                                tmpX1 = Integer.parseInt(s);
                                s = br.readLine();
                                tmpY1 = Integer.parseInt(s);
                                s = br.readLine();
                                tmpX2 = Integer.parseInt(s);
                                s = br.readLine();
                                tmpY2 = Integer.parseInt(s);
                                int tmpStroke;
                                s = br.readLine();
                                tmpStroke = Integer.parseInt(s);
                                Ellipse2D tmpElli = new Ellipse2D.Double(tmpX1, tmpY1, tmpX2 - tmpX1, tmpY2 - tmpY1);
                                currentElli = new MyEllipse();
                                currentElli.setEllipse(tmpElli);
                                currentElli.setColor(tmpRGB);
                                currentElli.setStroke(tmpStroke);
                                ellis.add(currentElli);
                                s = br.readLine();
                            }
                        }
                        s = br.readLine();
                        if (s.equals("words begin")) {
                            s = br.readLine();
                            while (!s.equals("words end")) {
                                //color, x, y, fontsize, fontname, s, isbold, isitalic
                                int[] tmpRGB = new int[3];
                                tmpRGB[0] = Integer.parseInt(s);
                                s = br.readLine();
                                tmpRGB[1] = Integer.parseInt(s);
                                s = br.readLine();
                                tmpRGB[2] = Integer.parseInt(s);
                                int tmpX, tmpY;
                                s = br.readLine();
                                tmpX = Integer.parseInt(s);
                                s = br.readLine();
                                tmpY = Integer.parseInt(s);
                                int tmpFontSize;
                                s = br.readLine();
                                tmpFontSize = Integer.parseInt(s);
                                String tmpFontName = br.readLine();
                                String text = br.readLine();
                                String isBold = br.readLine();
                                String isItalic = br.readLine();


                                MyWord w = new MyWord();
                                w.setColor(tmpRGB);
                                w.setS(text);
                                w.setX(tmpX);
                                w.setY(tmpY);
                                w.setFontName(tmpFontName);
                                w.setFontSize(tmpFontSize);
                                if (isBold.equals("isB")) {
                                    w.setBold(true);
                                } else
                                    w.setBold(false);
                                if (isItalic.equals("isI")) {
                                    w.setItalic(true);
                                } else
                                    w.setItalic(false);
                                words.add(w);
                                s = br.readLine();
                            }
                        }
                    } catch (Throwable e1) {
                        e1.printStackTrace();
                    }
                }
            }
            else if(e.getActionCommand().equals("save file"))
            {
                currentLine = null;
                currentElli = null;
                currentRect = null;
                currentWord = null;
                myLabel.setText("Now Saving File...");
                System.out.println("save file");
                fileDialog = new FileDialog(myFrame, "save file", FileDialog.SAVE);
                fileDialog.setVisible(true);
                String fileName = fileDialog.getFile();
                String filePath = fileDialog.getDirectory();
                if(fileName!=null&&filePath!=null) {
                    try {
                        FileWriter fw = new FileWriter(filePath + fileName);
                        //save colors, x1, y1, x2, y2, stroke
                        fw.write("lines begin\n");
                        for (MyLine l : lines) {
                            int[] colors = l.getColor();
                            fw.write(colors[0] + "\n" + colors[1] + "\n" + colors[2] + "\n");
                            fw.write((int) l.getLine().getX1() + "\n" + (int) l.getLine().getY1() + "\n" + (int) l.getLine().getX2() + "\n" + (int) l.getLine().getY2() + "\n");
                            fw.write(l.getStroke() + "\n");
                            //fw.write(l.getLine().getX1());
                        }
                        fw.write("lines end\n");
                        fw.write("rects begin\n");
                        for (MyRectangular r : rects) {
                            int[] colors = r.getColor();
                            fw.write(colors[0] + "\n" + colors[1] + "\n" + colors[2] + "\n");
                            fw.write((int) r.getRectangle().getMinX() + "\n" + (int) r.getRectangle().getMinY() + "\n" + (int) r.getRectangle().getMaxX() + "\n" + (int) r.getRectangle().getMaxY() + "\n");
                            fw.write(r.getStroke() + "\n");
                            //fw.write(l.getLine().getX1());
                        }
                        fw.write("rects end\n");
                        fw.write("ellis begin\n");
                        for (MyEllipse r : ellis) {
                            int[] colors = r.getColor();
                            fw.write(colors[0] + "\n" + colors[1] + "\n" + colors[2] + "\n");
                            fw.write((int) r.getEllipse().getMinX() + "\n" + (int) r.getEllipse().getMinY() + "\n" + (int) r.getEllipse().getMaxX() + "\n" + (int) r.getEllipse().getMaxY() + "\n");
                            fw.write(r.getStroke() + "\n");
                            //fw.write(l.getLine().getX1());
                        }
                        fw.write("ellis end\n");
                        //color, x, y, fontsize, fontname, s, isbold, isitalic
                        fw.write("words begin\n");
                        for (MyWord r : words) {
                            int[] colors = r.getColor();
                            fw.write(colors[0] + "\n" + colors[1] + "\n" + colors[2] + "\n");
                            fw.write((int) r.getX() + "\n" + (int) r.getY() + "\n" + (int) r.getFontSize() + "\n");
                            fw.write(r.getFontName() + "\n");
                            fw.write(r.getS() + "\n");
                            if (r.isBold())
                                fw.write("isB\n");
                            else
                                fw.write("notB\n");
                            if (r.isItalic())
                                fw.write("isI\n");
                            else
                                fw.write("notI\n");
                            //fw.write(l.getLine().getX1());
                        }
                        fw.write("words end\n");
                        fw.close();
                    } catch (Exception eee) {
                        eee.printStackTrace();
                    }
                }
            }
            else if(e.getActionCommand().equals("exit"))
            {
                myLabel.setText("Now Exiting!");
                dispose();
                System.exit(0);
            }
            else if(e.getActionCommand().equals("draw line"))
            {
                myLabel.setText("Draw Line");
                drawing = false;
                drawLine = true;
                drawRect = false;
                drawElli = false;
                drawWords = false;
                deletable = false;
                currentLine = null;
                currentElli = null;
                currentRect = null;
                currentWord = null;
            }
            else if(e.getActionCommand().equals("draw rectangle"))
            {
                myLabel.setText("Draw Rectangle");
                drawing = false;
                drawLine = false;
                drawRect = true;
                drawElli = false;
                drawWords = false;
                deletable = false;
                currentLine = null;
                currentElli = null;
                currentRect = null;
                currentWord = null;
            }
            else if(e.getActionCommand().equals("draw ellipse"))
            {
                myLabel.setText("Draw Ellipse");
                drawing = false;
                drawLine = false;
                drawRect = false;
                drawElli = true;
                drawWords = false;
                deletable = false;
                currentLine = null;
                currentElli = null;
                currentRect = null;
                currentWord = null;
            }
            else if(e.getActionCommand().equals("draw word"))
            {
                myLabel.setText("Draw Word");
                drawing = false;
                drawLine = false;
                drawRect = false;
                drawElli = false;
                drawWords = true;
                deletable = false;
                currentLine = null;
                currentElli = null;
                currentRect = null;
                currentWord = null;
            }
            else if(e.getActionCommand().equals("choose a shape"))
            {
                myLabel.setText("Please choose a shape");
                drawing = false;
                drawLine = false;
                drawRect = false;
                drawElli = false;
                drawWords = false;
                deletable = true;
                currentLine = null;
                currentElli = null;
                currentRect = null;
                currentWord = null;
            }
            else if(e.getActionCommand().equals("about"))
            {
                AboutMessage message = new AboutMessage();
            }
            redrawAll((Graphics2D) g);
        }
    }

    public void drawAThing(Graphics2D g)
    {
        g.setColor(new Color(colorDefault[0], colorDefault[1], colorDefault[2]));
        g.setStroke(new BasicStroke(lineWidth));
        //myText.setVisible(false);
        if(drawLine)
        {
            Line2D tmpLine = new Line2D.Double(sx, sy, ex, ey);
            currentLine = new MyLine();
            currentLine.setLine(tmpLine);
            currentLine.setColor(colorDefault);
            currentLine.setStroke(lineWidth);
            lines.add(currentLine);
            g.draw(tmpLine);
        }
        else if(drawRect)
        {
            Rectangle2D tmpRect = new Rectangle2D.Double(Math.min(ex,sx),Math.min(ey,sy),Math.abs(ex-sx),Math.abs(ey-sy));
            currentRect = new MyRectangular();
            currentRect.setRectangle(tmpRect);
            currentRect.setColor(colorDefault);
            currentRect.setStroke(lineWidth);
            rects.add(currentRect);
            g.draw(tmpRect);
        }
        else if(drawElli)
        {
            Ellipse2D tmpElli = new Ellipse2D.Double(Math.min(ex,sx),Math.min(ey,sy),Math.abs(ex-sx),Math.abs(ey-sy));
            currentElli = new MyEllipse();
            currentElli.setEllipse(tmpElli);
            currentElli.setColor(colorDefault);
            currentElli.setStroke(lineWidth);
            ellis.add(currentElli);
            g.draw(tmpElli);
        }
        else if(drawWords)
        {
            String s = myText.getText();
            MyWord w = new MyWord();
            w.setColor(colorDefault);
            w.setS(s);
            w.setX(sx + 2);
            w.setY(sy + 14);
            w.setFontName(fontName);
            w.setFontSize(fontSize);
            w.setBold(fontBold);
            w.setItalic(fontItalic);
            words.add(w);
            if(fontBold && fontItalic)
                g.setFont(new Font(fontName, Font.BOLD|Font.ITALIC, fontSize));
            else if(fontBold)
                g.setFont(new Font(fontName, Font.BOLD, fontSize));
            else if(fontItalic)
                g.setFont(new Font(fontName, Font.ITALIC, fontSize));
            else
                g.setFont(new Font(fontName, 0, fontSize));
            g.drawString(s, sx + 2, sy + 14);
        }
        //
        //repaint();
    }
    public void redrawAll(Graphics2D g)
    {
        //update(myPanel);
        myPanel.update(g);
        //myText.setVisible(fal);
        g.setColor(new Color(colorDefault[0], colorDefault[1], colorDefault[2]));
        //g.setStroke(new BasicStroke(5));
        for(MyLine l : lines)
        {
            //g.setColor(new Color(200,200,200));
            g.setColor(new Color(l.getColor()[0], l.getColor()[1], l.getColor()[2]));
            g.setStroke(new BasicStroke(l.getStroke()));
            if(type == 1 && currentLine == l)
                g.setColor(new Color(colorChoose[0], colorChoose[1], colorChoose[2]));
            g.draw(l.getLine());
            g.setColor(new Color(colorDefault[0], colorDefault[1], colorDefault[2]));
        }
        for(MyRectangular r : rects)
        {
            g.setColor(new Color(r.getColor()[0], r.getColor()[1], r.getColor()[2]));
            g.setStroke(new BasicStroke(r.getStroke()));
            if(type == 2 && currentRect == r)
                g.setColor(new Color(colorChoose[0], colorChoose[1], colorChoose[2]));
            g.draw(r.getRectangle());
            g.setColor(new Color(colorDefault[0], colorDefault[1], colorDefault[2]));
            //g.draw(r);
        }
        for(MyEllipse e : ellis)
        {
            //g.draw(e);
            g.setColor(new Color(e.getColor()[0], e.getColor()[1], e.getColor()[2]));
            g.setStroke(new BasicStroke(e.getStroke()));
            if(type == 3 && currentElli == e)
                g.setColor(new Color(colorChoose[0], colorChoose[1], colorChoose[2]));
            g.draw(e.getEllipse());
            g.setColor(new Color(colorDefault[0], colorDefault[1], colorDefault[2]));
        }
        for(MyWord w : words)
        {
            g.setColor(new Color(w.getColor()[0], w.getColor()[1], w.getColor()[2]));
            if(type == 4 && currentWord == w)
                g.setColor(new Color(colorChoose[0], colorChoose[1], colorChoose[2]));

            //g.setFont(new Font("Blackoak Std", fontBold?Font.BOLD:fontItalic?Font.ITALIC:0, 12));
            if(w.isBold() && w.isItalic())
                g.setFont(new Font(w.getFontName(), Font.BOLD|Font.ITALIC, w.getFontSize()));
            else if(w.isBold())
                g.setFont(new Font(w.getFontName(), Font.BOLD, w.getFontSize()));
            else if(w.isItalic())
                g.setFont(new Font(w.getFontName(), Font.ITALIC, w.getFontSize()));
            else
                g.setFont(new Font(w.getFontName(), 0, w.getFontSize()));
            g.drawString(w.getS(), w.getX(), w.getY());
            g.setColor(new Color(colorDefault[0], colorDefault[1], colorDefault[2]));
        }
        //myText.setVisible(false);
    }
    //the message
    class AboutMessage implements ActionListener {
        Dialog dlg;
        Panel p1 = new Panel();
        Panel p2 = new Panel();
        Label message = new Label("a small application, have fun!");
        Button btn = new Button("OK");

        AboutMessage() {
            dlg = new Dialog(myFrame, "about", false);
            btn.addActionListener(this);
            p1.add(message);
            p2.add(btn);
            dlg.add(p1, BorderLayout.NORTH);
            dlg.add(p2, BorderLayout.SOUTH);
            dlg.setSize(200, 100);
            dlg.setResizable(false);
            dlg.setLocation(550, 300);
            dlg.setVisible(true);
        }

        public void actionPerformed(ActionEvent e) {
            dlg.dispose();
        }
    }

    class ColorFontMessage implements ActionListener {
        Dialog dlg;
        Panel p1 = new Panel();  //color
        Panel p2 = new Panel();  //font
        Panel p3 = new Panel();  //ok
        JColorChooser colorChooser = new JColorChooser(Color.BLACK);
        Label label = new Label("You can choose a font from: 'Times New Roman', 'Cooper Black', 'Blackoak Std'), you can set font size, or the line width.      ");
        Label fontLabel = new Label("font:");
        TextField font = new TextField("Times New Roman");
        JCheckBox bold = new JCheckBox("bold");
        JCheckBox italic = new JCheckBox("italic");
        Label sizeLabel = new Label("font size:");
        TextField size = new TextField("15");
        Label strokeLabel = new Label("line width(for line, rect, elli):");
        TextField stroke =  new TextField("5");
        Button btnOK = new Button("OK");
        Button btnCancel = new Button("Cancel");

        ColorFontMessage() {
            dlg = new Dialog(myFrame, "about", false);
            //color

            p1.add(colorChooser);
            //font

            p2.add(label);
            p2.add(strokeLabel);
            p2.add(stroke);
            p2.add(fontLabel);
            font.setColumns(16);
            //font.setBounds(100, 100, 100, 30);
            p2.add(font, BorderLayout.NORTH);

            p2.add(bold);
            p2.add(italic);
            p2.add(sizeLabel);
            size.setColumns(5);
            p2.add(size);
            stroke.setColumns(5);

            //button
            btnCancel.addActionListener(this);
            btnOK.addActionListener(this);
            p3.add(btnOK);
            p3.add(btnCancel);

            dlg.add(p1, BorderLayout.NORTH);
            dlg.add(p2, BorderLayout.CENTER);
            dlg.add(p3, BorderLayout.SOUTH);
            dlg.setSize(800, 500);
            dlg.setResizable(false);
            dlg.setLocation(550, 300);
            dlg.setVisible(true);
        }

        public void actionPerformed(ActionEvent e) {
            //System.out.println(e.getActionCommand());
            if(e.getActionCommand().equals("OK"))
            {
                colorDefault[0] = colorChooser.getColor().getRed();
                colorDefault[1] = colorChooser.getColor().getGreen();
                colorDefault[2] = colorChooser.getColor().getBlue();
                String fontNameSave = fontName;
                fontName = font.getText();
                if(!(fontName.equals("Times New Roman")||fontName.equals("Cooper Black")||fontName.equals("Blackoak Std")))
                {
                    fontName = fontNameSave;
                }
                try {
                    fontSize = Integer.parseInt(size.getText());
                }catch (Exception ee)
                {
                    fontSize = 15;
                }
                try {
                    lineWidth = Integer.parseInt(stroke.getText());
                }catch (Exception ee)
                {
                    lineWidth = 4;
                }
                fontBold = bold.isSelected();
                fontItalic = italic.isSelected();
            }
            dlg.dispose();
        }
    }

    class MyEllipse
    {
        private Ellipse2D ellipse;
        private int ColorRed;
        private int ColorGreen;
        private int ColorBlue;
        private int stroke;
        public void setStroke(int i) {stroke = i;}
        public int getStroke(){return stroke;}
        public void setEllipse(Ellipse2D e) {ellipse = e;}
        public void setColor(int[] c)
        {
            ColorRed = c[0];
            ColorGreen = c[1];
            ColorBlue = c[2];
        }
        public Ellipse2D getEllipse() {return ellipse;}
        public int[] getColor()
        {
            int[] tmp = {ColorRed, ColorGreen, ColorBlue};
            return tmp;
        }
    }
    class MyLine
    {
        private Line2D line;
        private int ColorRed;
        private int ColorGreen;
        private int ColorBlue;
        private int stroke;
        public void setStroke(int i) {stroke = i;}
        public int getStroke(){return stroke;}
        public void setLine(Line2D l) {line = l;}
        public void setColor(int[] c)
        {
            ColorRed = c[0];
            ColorGreen = c[1];
            ColorBlue = c[2];
        }
        public Line2D getLine() {return line;}
        public int[] getColor()
        {
            int[] tmp = {ColorRed, ColorGreen, ColorBlue};
            return tmp;
        }
    }
    class MyRectangular
    {
        private Rectangle2D rectangle;
        private int ColorRed;
        private int ColorGreen;
        private int ColorBlue;
        private int stroke;
        public void setStroke(int i) {stroke = i;}
        public int getStroke(){return stroke;}
        public void setRectangle(Rectangle2D r) {rectangle = r;}
        public void setColor(int[] c)
        {
            ColorRed = c[0];
            ColorGreen = c[1];
            ColorBlue = c[2];
        }
        public Rectangle2D getRectangle() {return rectangle;}
        public int[] getColor()
        {
            int[] tmp = {ColorRed, ColorGreen, ColorBlue};
            return tmp;
        }
    }
    class MyWord
    {
        private String s;
        private String fontName;
        private int fontSize;
        private boolean bold;
        private boolean italic;
        private int X, Y;
        private int ColorRed;
        private int ColorGreen;
        private int ColorBlue;
        public void setFontName(String s){fontName = s;}
        public void setFontSize(int i){fontSize = i;}
        public void setBold(boolean b){bold = b;}
        public void setItalic(boolean b){italic = b;}
        public String getFontName(){return fontName;}
        public int getFontSize(){return  fontSize;}
        public boolean isBold(){return bold;}
        public boolean isItalic(){return italic;}
        public String getS() {return s;}
        public int getX() {return X;}
        public int getY() {return Y;}
        public void setS(String ss) {s = ss;}
        public void setX(int x) {X = x;}
        public void setY(int y) {Y = y;}
        public boolean contains(Point2D p)
        {
            if(p.getX() > X && p.getX() < X+s.length()*8+fontSize-15 && p.getY() > Y-10 && p.getY() < Y+10)
                return true;
            return false;
        }
        public void setColor(int[] c)
        {
            ColorRed = c[0];
            ColorGreen = c[1];
            ColorBlue = c[2];
        }
        public int[] getColor()
        {
            int[] tmp = {ColorRed, ColorGreen, ColorBlue};
            return tmp;
        }
    }

    public static void main(String args[])
    {
        DrawBoard drawBoard = new DrawBoard();
        drawBoard.display();
    }
}
