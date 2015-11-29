/*
created by Chenyang Ji, sophomore.
a mips assembler, and you can even run
some simple mips codes and also debug
using this tool!
*/
package mips;
import javax.swing.*;
import javax.swing.event.*;

import java.awt.event.*;
import java.awt.*;
import java.util.HashMap;
import java.util.Map;

public class Test{
	public static void main(String args[])throws Exception{
	    	NewFrame1 frame = new NewFrame1();
	        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//一定要设置关闭
	        frame.setVisible(true);
	        
	        
	    }
	}
class NewFrame1 extends JFrame{
	    private JButton button1,button2,button3,button0,button4;
	    private JTextArea text1 = new JTextArea(), text2= new JTextArea();
	    private JScrollPane pane1 = new JScrollPane(text1);
	    private JScrollPane pane2 = new JScrollPane(text2);
	    private JTextField tzero,tv0,tv1,ta0,ta1,ta2,ta3,tt0,tt1,tt2,tt3,tt4,tt5,tt6,tt7,tt8,tt9,ts0,ts1,ts2,ts3,ts4,ts5,ts6,ts7,tgp,tsp,tfp,tra,tpc;
	    private JLabel label1,label2,label3,label4,label5,label6,label7,label8,label9,label10,label11;
	    private JLabel label12,label13,label14,label15,label16,label17,label18,label19,label20,label21,label22;
	    private JLabel label23,label24,label25,label26,label27,label28,label0,labelpc;
	    public int i = 0;
		   int flag = 0;
		   String[] row; 
         String[] word = null;
         String opcode, regs, regt, regd;
         int nums,numt,numd;
         String imstr;
         int imnum;
         int a, b;
         int pc;
         int[] reg = new int[32];
 		Map<String,String> map = new HashMap<String,String>();
 		Map<String,String> lab = new HashMap<String,String>();
	    
	    public NewFrame1(){
	        super();
	        this.setSize(800,700);
	        this.getContentPane().setLayout(null);//设置布局控制器
	        pane1.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
	        pane1.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
	        pane2.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
	        pane2.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
	       // this.add(this.getTextArea2(),null);//添加文本框
	        
	        add(pane1);	 
	        add(pane2);

	        pane1.setBounds(96,49,320,200);
	        
	        pane2.setBounds(96, 300, 320, 200);

	        //this.add(this.getTextArea1(),null);//添加文本框

	        this.add(this.getButton(),null);//添加按钮
	        this.add(this.getButton2(),null);//添加按钮
	        this.add(this.getButton3(),null);
	        this.add(this.getButton0(),null);
	        this.add(this.getButton4(),null);
	        this.add(this.getLabel1(),null);
	        this.add(this.getLabel2(),null);
	        this.add(this.getLabel3(),null);
	        this.add(this.getLabel4(),null);
	        this.add(this.getLabel5(),null);
	        this.add(this.getLabel6(),null);
	        this.add(this.getLabel7(),null);
	        this.add(this.getLabel8(),null);
	        this.add(this.getLabel9(),null);
	        this.add(this.getLabel10(),null);
	        this.add(this.getLabel11(),null);
	        this.add(this.getLabel12(),null);
	        this.add(this.getLabel13(),null);
	        this.add(this.getLabel14(),null);
	        this.add(this.getLabel15(),null);
	        this.add(this.getLabel16(),null);
	        this.add(this.getLabel17(),null);
	        this.add(this.getLabel18(),null);
	        this.add(this.getLabel19(),null);
	        this.add(this.getLabel20(),null);
	        this.add(this.getLabel21(),null);
	        this.add(this.getLabel22(),null);
	        this.add(this.getLabel23(),null);
	        this.add(this.getLabel24(),null);
	        this.add(this.getLabel25(),null);
	        this.add(this.getLabel26(),null);
	        this.add(this.getLabel27(),null);
	        this.add(this.getLabel28(),null);
	        this.add(this.getLabel0(),null);
	        this.add(this.getLabelpc(),null);
	        this.add(this.getTextField0(),null);//添加文本框
	        this.add(this.getTextField1(),null);
	        this.add(this.getTextField2(),null);
	        this.add(this.getTextField3(),null);
	        this.add(this.getTextField4(),null);
	        this.add(this.getTextField5(),null);
	        this.add(this.getTextField6(),null);
	        this.add(this.getTextField7(),null);
	        this.add(this.getTextField8(),null);
	        this.add(this.getTextField9(),null);
	        this.add(this.getTextField10(),null);
	        this.add(this.getTextField11(),null);
	        this.add(this.getTextField12(),null);
	        this.add(this.getTextField13(),null);
	        this.add(this.getTextField14(),null);
	        this.add(this.getTextField15(),null);
	        this.add(this.getTextField16(),null);
	        this.add(this.getTextField17(),null);
	        this.add(this.getTextField18(),null);
	        this.add(this.getTextField19(),null);
	        this.add(this.getTextField20(),null);
	        this.add(this.getTextField21(),null);
	        this.add(this.getTextField22(),null);
	        this.add(this.getTextField23(),null);
	        this.add(this.getTextField24(),null);
	        this.add(this.getTextField25(),null);
	        this.add(this.getTextField26(),null);
	        this.add(this.getTextField27(),null);
	        this.add(this.getTextField28(),null);
	        this.add(this.getTextFieldpc(),null);

	        this.setTitle("汇编器by吉辰阳:)");//设置窗口标题

	    }
	    
	    private JButton getButton0(){
	        if(button0==null){
	            button0 = new JButton();
	            button0.setBounds(286,260,100,27);
	            button0.setText("To Code");
	            button0.setToolTipText("OK");
	            button0.addActionListener(new CodeButton());//添加监听器类，其主要的响应都由监听器类的方法实现

	        }
	        return button0;
	    }
	    private JButton getButton(){
	        if(button1==null){
	            button1 = new JButton();
	            button1.setBounds(146,260,100,27);
	            button1.setText("To Hex");
	            button1.setToolTipText("OK");
	            button1.addActionListener(new HelloButton());//添加监听器类，其主要的响应都由监听器类的方法实现

	        }
	        return button1;
	    }
	    private JButton getButton2(){
	        if(button2==null){
	            button2 = new JButton();
	            button2.setBounds(146,510,100,27);
	            button2.setText("By Step!");
	            button2.setToolTipText("OK");
	            button2.addActionListener(new DoButton());//添加监听器类，其主要的响应都由监听器类的方法实现

	        }
	        return button2;
	    }
	    private JButton getButton3(){
	        if(button3==null){
	            button3 = new JButton();
	            button3.setBounds(286,510,100,27);
	            button3.setText("To End!");
	            button3.setToolTipText("OK");
	            button3.addActionListener(new EndButton());//添加监听器类，其主要的响应都由监听器类的方法实现

	        }
	        return button3;
	    }
	    private JButton getButton4(){
	        if(button4==null){
	            button4 = new JButton();
	            button4.setBounds(216,560,100,27);
	            button4.setText("Reset!");
	            button4.setToolTipText("OK");
	            button4.addActionListener(new ResetButton());//添加监听器类，其主要的响应都由监听器类的方法实现

	        }
	        return button4;
	    }
	///////////////////////////////////////////////////////////
	    
	  
	    private class HelloButton implements ActionListener{
	        public void actionPerformed(ActionEvent e){
	            String[] row = text1.getText().split("\n");
	            String[] word = null;
	            String opcode, regs, regt, regd, bin = null;
	            String bopcode = null,  bregs= null, bregt= null, bregd= null, btail= null;
	            String h1, h2, h3, h4, h5, h6, h7, h8;
	            String imstr;
	            int imnum;
	            int tmp = 0;
	            int pc = 0;
	            text2.setText("");
	            for(int i = 0; i<row.length; i++){
	            	row[i] = row[i].replaceAll(" +", " ");
	            	if(row[i].equals(""))
	            		continue;
	            	if(row[i].equals(" "))
	            		continue;
	            	word = row[i].split(": |:|\\)|\\(| ,|, | |,");
	            	opcode = word[0];
	            	if(opcode.equals("bgt")||opcode.equals("bge")||opcode.equals("blt")||opcode.equals("ble")||opcode.equals("move")||
	            	opcode.equals("xor")||opcode.equals("nor")||opcode.equals("add")||opcode.equals("sub")||opcode.equals("and")||opcode.equals("or")||opcode.equals("slt")
	            	||opcode.equals("sll")||opcode.equals("srl")||opcode.equals("addi")||opcode.equals("ori")||opcode.equals("jr")||
	            	opcode.equals("beq")||opcode.equals("bne")||opcode.equals("lw")||opcode.equals("sw")||opcode.equals("j")||opcode.equals("jal")
	            	||opcode.equals("sra")||opcode.equals("lui")== true){
	            		tmp++;
	            	}
	            	else{
	            		opcode = word[1];
	            		if(opcode.equals("bgt")||opcode.equals("bge")||opcode.equals("blt")||opcode.equals("ble")||opcode.equals("move")||
	        	            	opcode.equals("xor")||opcode.equals("nor")||opcode.equals("add")||opcode.equals("sub")||opcode.equals("and")||opcode.equals("or")||opcode.equals("slt")
	        	            	||opcode.equals("sll")||opcode.equals("srl")||opcode.equals("addi")||opcode.equals("ori")||opcode.equals("jr")||
	        	            	opcode.equals("beq")||opcode.equals("bne")||opcode.equals("lw")||opcode.equals("sw")||opcode.equals("j")||opcode.equals("jal")
	        	            	||opcode.equals("sra")||opcode.equals("lui")== true){
	            			lab.put(word[0], Integer.toString(tmp*4));
	            			tmp++;
	            			row[i] = word[1];
	            			for(int j = 1; j <word.length-1; j++)
	            				row[i] += (" "+word[j+1]);
	            		}
	            	}
	            }
	           // imstr = lab.get("loop");	
	           // System.out.println(Integer.valueOf(lab.get("loop")));
	            for(int i = 0; i<row.length; i++){
	            	//row[i] = row[i].replaceAll(" +", " ");
	            	if(row[i].equals(""))
	            		continue;
	            	if(row[i].equals(" "))
	            		continue;
	            	word = row[i].split("\\)|\\(| ,|, | |,");
	            	opcode = word[0];
	            	if(opcode.equals("bgt")||opcode.equals("bge")||opcode.equals("blt")||opcode.equals("ble")||opcode.equals("move") == true){
	            		if(opcode.equals("move")){
	            			row[i] = "add "+word[1]+", "+"$zero"+", "+word[2];
	            			i--;
	            			continue;
	            		}
	            		else if(opcode.equals("ble")){
		            		bregd = "11001";
		            		regs = word[2];
		        			regt = word[1]; 
		            		bregs = convert(regs);
		            		bregt = convert(regt);
	            			bopcode = "000000";
		            		btail = "00000101010";	            		
			        		bin = bopcode+bregs+bregt+bregd+btail;
			        		h1 = Long.toHexString(Long.parseLong(bin.substring(0, 4),2));
			        		h2 = Long.toHexString(Long.parseLong(bin.substring(4, 8),2));
			        		h3 = Long.toHexString(Long.parseLong(bin.substring(8, 12),2));
			        		h4 = Long.toHexString(Long.parseLong(bin.substring(12, 16),2));
			        		h5 = Long.toHexString(Long.parseLong(bin.substring(16, 20),2));
			        		h6 = Long.toHexString(Long.parseLong(bin.substring(20, 24),2));
			        		h7 = Long.toHexString(Long.parseLong(bin.substring(24, 28),2));
			        		h8 = Long.toHexString(Long.parseLong(bin.substring(28, 32),2));
			        		text2.append(h1+h2+h3+h4+h5+h6+h7+h8+"\n");
			        		
			        		bregs = "11001";
		        			bregt = "00000"; 
		            		bopcode = "000100";
		            		imstr = word[3];
	        				
		            		if(imstr.replace('-', '0').matches("[0-9]*") != true){
		            			imstr = lab.get(imstr);
		            			imnum = Integer.valueOf(imstr);
		            			imnum/=4;
		            			imnum -= (pc/4+1);
		            		}
		            		else
		            			imnum = Integer.valueOf(imstr);
		            		
	        				imstr = Integer.toBinaryString(imnum);
	        				while(imstr.length()<16){
	        					imstr = "0"+imstr;
	        				}
	        				while(imstr.length()>16){
	        					imstr = imstr.substring(16, 32);
	        				}
	        				
	        			
			        		bin = bopcode+bregs+bregt+imstr;
			        		h1 = Long.toHexString(Long.parseLong(bin.substring(0, 4),2));
			        		h2 = Long.toHexString(Long.parseLong(bin.substring(4, 8),2));
			        		h3 = Long.toHexString(Long.parseLong(bin.substring(8, 12),2));
			        		h4 = Long.toHexString(Long.parseLong(bin.substring(12, 16),2));
			        		h5 = Long.toHexString(Long.parseLong(bin.substring(16, 20),2));
			        		h6 = Long.toHexString(Long.parseLong(bin.substring(20, 24),2));
			        		h7 = Long.toHexString(Long.parseLong(bin.substring(24, 28),2));
			        		h8 = Long.toHexString(Long.parseLong(bin.substring(28, 32),2));
			        		text2.append(h1+h2+h3+h4+h5+h6+h7+h8+"\n");
	            			continue;
	            		}
	            		else if(opcode.equals("blt")){
		            		bregd = "11001";
		            		regt = word[2];
		        			regs = word[1]; 
		            		bregs = convert(regs);
		            		bregt = convert(regt);
	            			bopcode = "000000";
		            		btail = "00000101010";	            		
			        		bin = bopcode+bregs+bregt+bregd+btail;
			        		h1 = Long.toHexString(Long.parseLong(bin.substring(0, 4),2));
			        		h2 = Long.toHexString(Long.parseLong(bin.substring(4, 8),2));
			        		h3 = Long.toHexString(Long.parseLong(bin.substring(8, 12),2));
			        		h4 = Long.toHexString(Long.parseLong(bin.substring(12, 16),2));
			        		h5 = Long.toHexString(Long.parseLong(bin.substring(16, 20),2));
			        		h6 = Long.toHexString(Long.parseLong(bin.substring(20, 24),2));
			        		h7 = Long.toHexString(Long.parseLong(bin.substring(24, 28),2));
			        		h8 = Long.toHexString(Long.parseLong(bin.substring(28, 32),2));
			        		text2.append(h1+h2+h3+h4+h5+h6+h7+h8+"\n");
			        		
			        		bregs = "11001";
		        			bregt = "00000"; 
		            		bopcode = "000101";
		            		imstr = word[3];
		            		
		            		if(imstr.replace('-', '0').matches("[0-9]*") != true){
		            			imstr = lab.get(imstr);
		            			imnum = Integer.valueOf(imstr);
		            			imnum/=4;
		            			imnum -= (pc/4+1);
		            		}
		            		else
		            			imnum = Integer.valueOf(imstr);
		            		
	        				imstr = Integer.toBinaryString(imnum);
	        				while(imstr.length()<16){
	        					imstr = "0"+imstr;
	        				}
	        				while(imstr.length()>16){
	        					imstr = imstr.substring(16, 32);
	        				}
		            		
			        		bin = bopcode+bregs+bregt+imstr;
			        		h1 = Long.toHexString(Long.parseLong(bin.substring(0, 4),2));
			        		h2 = Long.toHexString(Long.parseLong(bin.substring(4, 8),2));
			        		h3 = Long.toHexString(Long.parseLong(bin.substring(8, 12),2));
			        		h4 = Long.toHexString(Long.parseLong(bin.substring(12, 16),2));
			        		h5 = Long.toHexString(Long.parseLong(bin.substring(16, 20),2));
			        		h6 = Long.toHexString(Long.parseLong(bin.substring(20, 24),2));
			        		h7 = Long.toHexString(Long.parseLong(bin.substring(24, 28),2));
			        		h8 = Long.toHexString(Long.parseLong(bin.substring(28, 32),2));
			        		text2.append(h1+h2+h3+h4+h5+h6+h7+h8+"\n");
	            			continue;
	            		}
	            		else if(opcode.equals("bge")){
		            		bregd = "11001";
		            		regt = word[2];
		        			regs = word[1]; 
		            		bregs = convert(regs);
		            		bregt = convert(regt);
	            			bopcode = "000000";
		            		btail = "00000101010";	            		
			        		bin = bopcode+bregs+bregt+bregd+btail;
			        		h1 = Long.toHexString(Long.parseLong(bin.substring(0, 4),2));
			        		h2 = Long.toHexString(Long.parseLong(bin.substring(4, 8),2));
			        		h3 = Long.toHexString(Long.parseLong(bin.substring(8, 12),2));
			        		h4 = Long.toHexString(Long.parseLong(bin.substring(12, 16),2));
			        		h5 = Long.toHexString(Long.parseLong(bin.substring(16, 20),2));
			        		h6 = Long.toHexString(Long.parseLong(bin.substring(20, 24),2));
			        		h7 = Long.toHexString(Long.parseLong(bin.substring(24, 28),2));
			        		h8 = Long.toHexString(Long.parseLong(bin.substring(28, 32),2));
			        		text2.append(h1+h2+h3+h4+h5+h6+h7+h8+"\n");
			        		
			        		bregs = "11001";
		        			bregt = "00000"; 
		        			bopcode = "000100";
		            		imstr = word[3];
		            		
		            		if(imstr.replace('-', '0').matches("[0-9]*") != true){
		            			imstr = lab.get(imstr);
		            			imnum = Integer.valueOf(imstr);
		            			imnum/=4;
		            			imnum -= (pc/4+1);
		            		}
		            		else
		            			imnum = Integer.valueOf(imstr);
		            		
	        				imstr = Integer.toBinaryString(imnum);
	        				while(imstr.length()<16){
	        					imstr = "0"+imstr;
	        				}
	        				while(imstr.length()>16){
	        					imstr = imstr.substring(16, 32);
	        				}
		            		
			        		bin = bopcode+bregs+bregt+imstr;
			        		h1 = Long.toHexString(Long.parseLong(bin.substring(0, 4),2));
			        		h2 = Long.toHexString(Long.parseLong(bin.substring(4, 8),2));
			        		h3 = Long.toHexString(Long.parseLong(bin.substring(8, 12),2));
			        		h4 = Long.toHexString(Long.parseLong(bin.substring(12, 16),2));
			        		h5 = Long.toHexString(Long.parseLong(bin.substring(16, 20),2));
			        		h6 = Long.toHexString(Long.parseLong(bin.substring(20, 24),2));
			        		h7 = Long.toHexString(Long.parseLong(bin.substring(24, 28),2));
			        		h8 = Long.toHexString(Long.parseLong(bin.substring(28, 32),2));
			        		text2.append(h1+h2+h3+h4+h5+h6+h7+h8+"\n");
	            			continue;
	            		}
	            		else if(opcode.equals("bgt")){
		            		bregd = "11001";
		            		regs = word[2];
		        			regt = word[1]; 
		            		bregs = convert(regs);
		            		bregt = convert(regt);
	            			bopcode = "000000";
		            		btail = "00000101010";	            		
			        		bin = bopcode+bregs+bregt+bregd+btail;
			        		h1 = Long.toHexString(Long.parseLong(bin.substring(0, 4),2));
			        		h2 = Long.toHexString(Long.parseLong(bin.substring(4, 8),2));
			        		h3 = Long.toHexString(Long.parseLong(bin.substring(8, 12),2));
			        		h4 = Long.toHexString(Long.parseLong(bin.substring(12, 16),2));
			        		h5 = Long.toHexString(Long.parseLong(bin.substring(16, 20),2));
			        		h6 = Long.toHexString(Long.parseLong(bin.substring(20, 24),2));
			        		h7 = Long.toHexString(Long.parseLong(bin.substring(24, 28),2));
			        		h8 = Long.toHexString(Long.parseLong(bin.substring(28, 32),2));
			        		text2.append(h1+h2+h3+h4+h5+h6+h7+h8+"\n");
			        		
			        		bregs = "11001";
		        			bregt = "00000"; 
		            		bopcode = "000101";
		            		imstr = word[3];
		            		
		            		if(imstr.replace('-', '0').matches("[0-9]*") != true){
		            			imstr = lab.get(imstr);
		            			imnum = Integer.valueOf(imstr);
		            			imnum/=4;
		            			imnum -= (pc/4+1);
		            		}
		            		else
		            			imnum = Integer.valueOf(imstr);
		            		
	        				imstr = Integer.toBinaryString(imnum);
	        				while(imstr.length()<16){
	        					imstr = "0"+imstr;
	        				}
	        				while(imstr.length()>16){
	        					imstr = imstr.substring(16, 32);
	        				}
		            		
			        		bin = bopcode+bregs+bregt+imstr;
			        		h1 = Long.toHexString(Long.parseLong(bin.substring(0, 4),2));
			        		h2 = Long.toHexString(Long.parseLong(bin.substring(4, 8),2));
			        		h3 = Long.toHexString(Long.parseLong(bin.substring(8, 12),2));
			        		h4 = Long.toHexString(Long.parseLong(bin.substring(12, 16),2));
			        		h5 = Long.toHexString(Long.parseLong(bin.substring(16, 20),2));
			        		h6 = Long.toHexString(Long.parseLong(bin.substring(20, 24),2));
			        		h7 = Long.toHexString(Long.parseLong(bin.substring(24, 28),2));
			        		h8 = Long.toHexString(Long.parseLong(bin.substring(28, 32),2));
			        		text2.append(h1+h2+h3+h4+h5+h6+h7+h8+"\n");
	            			continue;
	            		}
	            		pc+=4;
	            	}
	            	
	            	else if(opcode.equals("xor")||opcode.equals("nor")||opcode.equals("add")||opcode.equals("sub")||opcode.equals("and")||opcode.equals("or")||opcode.equals("slt") == true) //R type with 3 reg
	            	{
	            		
	            		regd =word[1];
	            		regs = word[2];
	        			regt = word[3]; 
	            		bopcode = "000000";
	            		bregd = convert(regd);
	            		bregs = convert(regs);
	            		bregt = convert(regt);
	            		if(opcode.equals("add"))
	            			btail = "00000100000";
	            		if(opcode.equals("sub"))
	            			btail = "00000100010";
	            		if(opcode.equals("and"))
	            			btail = "00000100100";
	            		if(opcode.equals("or"))
	            			btail = "00000100101";
	            		if(opcode.equals("slt"))
	            			btail = "00000101010";
	            		if(opcode.equals("nor"))
	            			btail = "00000100111";
	            		if(opcode.equals("xor"))
	            			btail = "00000100110";
		        		bin = bopcode+bregs+bregt+bregd+btail;
		        		pc+=4;
	            	}
	            	
	            	else if(opcode.equals("sll")||opcode.equals("srl")){
        				regd = word[1];
        				regt = word[2];
        				imstr = word[3];
        				imnum = Integer.valueOf(imstr);
        				imstr = Integer.toBinaryString(imnum);
        				while(imstr.length()<5){
        					imstr = "0"+imstr;
        				}
	            		bopcode = "000000";
	            		bregs = "00000";
	            		bregd = convert(regd);
	            		bregt = convert(regt);
	            		
	            		if(opcode.equals("sll"))
	    					btail = imstr + "000000";
	    				if(opcode.equals("srl"))
	    					btail = imstr + "000010";
		        		bin = bopcode+bregs+bregt+bregd+btail;
		        		pc+=4;
	            	}
    				    				
	            	else if(opcode.equals("jr")){
    					regs = word[1];
    					bopcode = "000000";
	            		bregd = "00000";
	            		bregt = "00000";
	            		bregs = convert(regs);
    					btail = "00000001000";
    	        		bin = bopcode+bregs+bregt+bregd+btail;
    	        		pc+=4;
    				}
    					
    				
    				else if(opcode.equals("addi")||opcode.equals("ori") == true) //i type 1
	            	{
    					
	            		regt = word[1];
	        			regs = word[2]; 
	            		if(opcode.equals("addi"))
	            			bopcode = "001000";
	            		if(opcode.equals("ori"))
	            			bopcode = "001101";
	            		
	            		bregs = convert(regs);
	            		bregt = convert(regt);
	            		imstr = word[3];
        				imnum = Integer.valueOf(imstr);
        				imstr = Integer.toBinaryString(imnum);
        				while(imstr.length()<16){
        					imstr = "0"+imstr;
        				}
        				while(imstr.length()>16){
        					imstr = imstr.substring(16, 32);
        				}

		        		bin = bopcode+bregs+bregt+imstr;
		        		pc+=4;
	            	}
    				
    				else if(opcode.equals("beq")||opcode.equals("bne") == true) //i type 1
	            	{
    					
    					regs = word[1];
	        			regt = word[2]; 

	            		if(opcode.equals("beq"))
	            			bopcode = "000100";
	            		if(opcode.equals("bne"))
	            			bopcode = "000101";
	            		
	            		bregs = convert(regs);
	            		bregt = convert(regt);
	            		imstr = word[3];
	            		if(imstr.replace('-', '0').matches("[0-9]*") != true){
	            			imstr = lab.get(imstr);
	            			imnum = Integer.valueOf(imstr);
	            			imnum/=4;
	            			imnum -= (pc/4+1);
	            		}
	            		else
	            			imnum = Integer.valueOf(imstr);
	            		
        				imstr = Integer.toBinaryString(imnum);
        				while(imstr.length()<16){
        					imstr = "0"+imstr;
        				}
        				while(imstr.length()>16){
        					imstr = imstr.substring(16, 32);
        				}
        				
		        		bin = bopcode+bregs+bregt+imstr;
		        		pc+=4;
	            	}
    				
    				else if(opcode.equals("lw")||opcode.equals("sw") == true) //i type 1
	            	{
    					
    					regt = word[1];
	        			regs = word[3]; 

	            		if(opcode.equals("lw"))
	            			bopcode = "100011";
	            		if(opcode.equals("sw"))
	            			bopcode = "101011";
	            		
	            		bregs = convert(regs);
	            		bregt = convert(regt);
	            		imstr = word[2];
        				imnum = Integer.valueOf(imstr);
        				imstr = Integer.toBinaryString(imnum);
        				while(imstr.length()<16){
        					imstr = "0"+imstr;
        				}
        				while(imstr.length()>16){
        					imstr = imstr.substring(16, 32);
        				}

		        		bin = bopcode+bregs+bregt+imstr;
		        		pc+=4;
	            	}
    				
    				else if(opcode.equals("j")||opcode.equals("jal") == true) //i type 1
	            	{

	            		if(opcode.equals("j"))
	            			bopcode = "000010";
	            		if(opcode.equals("jal"))
	            			bopcode = "000011";
	            		imstr = word[1];
	            			            		
	            		if(imstr.replace('-', '0').matches("[0-9]*") != true){
	            			imstr = lab.get(imstr);
	            			imnum = Integer.valueOf(imstr);
	        				imnum/=4;	
	            		}
	            		else
	            			imnum = Integer.valueOf(imstr);

        				imstr = Integer.toBinaryString(imnum);
        				while(imstr.length()<26){
        					imstr = "0"+imstr;
        				}

		        		bin = bopcode+imstr;
		        		pc+=4;
	            	}
    				else if(opcode.equals("lui") == true) //lui
	            	{
	            			bopcode = "001111";
	            			regt = word[1];
		            		bregt = convert(regt);
		            		imstr = word[2];
	        				imnum = Integer.valueOf(imstr);
	        				imstr = Integer.toBinaryString(imnum);
	        				while(imstr.length()<16){
	        					imstr = "0"+imstr;
	        				}
	        				while(imstr.length()>16){
	        					imstr = imstr.substring(16, 32);
	        				}
		        		bin = bopcode+"00000"+bregt+imstr;
		        		pc+=4;
	            	}
    				
    				else if(opcode.equals("sra") == true) //lui
	            	{
    					regd = word[1];
        				regt = word[2];
        				imstr = word[3];
        				imnum = Integer.valueOf(imstr);
        				imstr = Integer.toBinaryString(imnum);
        				while(imstr.length()<5){
        					imstr = "0"+imstr;
        				}
	            		bopcode = "000000";
	            		bregs = "00000";
	            		bregd = convert(regd);
	            		bregt = convert(regt);
	    				btail = imstr + "000011";
		        		bin = bopcode+bregs+bregt+bregd+btail;
		        		pc+=4;
	            	}
    				else 
    					continue;
    				
    				if(bin.substring(0, 4)==null||bin.substring(4, 8)==null||
    					bin.substring(8, 12)==null||bin.substring(12, 16)==null||
    					bin.substring(16, 20)==null||bin.substring(20, 24)==null||
    					bin.substring(24, 28)==null||bin.substring(28, 32)==null){
    					continue;
    				}
    				
	        		h1 = Long.toHexString(Long.parseLong(bin.substring(0, 4),2));
	        		h2 = Long.toHexString(Long.parseLong(bin.substring(4, 8),2));
	        		h3 = Long.toHexString(Long.parseLong(bin.substring(8, 12),2));
	        		h4 = Long.toHexString(Long.parseLong(bin.substring(12, 16),2));
	        		h5 = Long.toHexString(Long.parseLong(bin.substring(16, 20),2));
	        		h6 = Long.toHexString(Long.parseLong(bin.substring(20, 24),2));
	        		h7 = Long.toHexString(Long.parseLong(bin.substring(24, 28),2));
	        		h8 = Long.toHexString(Long.parseLong(bin.substring(28, 32),2));
	        		text2.append(h1+h2+h3+h4+h5+h6+h7+h8+"\n");
	            }
	            //text2.append(row[i]+"yes\n");
	            
	            
	            
	            
	        }
	        public String convert(String reg){
	        	String res = null;
	        	if(reg.equals("$zero"))
	        		res = "00000";
	        	else if(reg.equals("$at"))
	        		res = "00001";
	        	else if(reg.equals("$v0"))
	        		res = "00010";
	        	else if(reg.equals("$v1"))
	        		res = "00011";
	        	else if(reg.equals("$a0"))
	        		res = "00100";
	        	else if(reg.equals("$a1"))
	        		res = "00101";
	        	else if(reg.equals("$a2"))
	        		res = "00110";
	        	else if(reg.equals("$a3"))
	        		res = "00111";
	        	else if(reg.equals("$t0"))
	        		res = "01000";
	        	else if(reg.equals("$t1"))
	        		res = "01001";
	        	else if(reg.equals("$t2"))
	        		res = "01010";
	        	else if(reg.equals("$t3"))
	        		res = "01011";
	        	else if(reg.equals("$t4"))
	        		res = "01100";
	        	else if(reg.equals("$t5"))
	        		res = "01101";
	        	else if(reg.equals("$t6"))
	        		res = "01110";
	        	else if(reg.equals("$t7"))
	        		res = "01111";
	        	else if(reg.equals("$s0"))
	        		res = "10000";
	        	else if(reg.equals("$s1"))
	        		res = "10001";
	        	else if(reg.equals("$s2"))
	        		res = "10010";
	        	else if(reg.equals("$s3"))
	        		res = "10011";
	        	else if(reg.equals("$s4"))
	        		res = "10100";
	        	else if(reg.equals("$s5"))
	        		res = "10101";
	        	else if(reg.equals("$s6"))
	        		res = "10110";
	        	else if(reg.equals("$s7"))
	        		res = "10111";
	        	else if(reg.equals("$t8"))
	        		res = "11000";
	        	else if(reg.equals("$t9"))
	        		res = "11001";
	        	else if(reg.equals("$k0"))
	        		res = "11010";
	        	else if(reg.equals("$k1"))
	        		res = "11011";
	        	else if(reg.equals("$gp"))
	        		res = "11100";
	        	else if(reg.equals("$sp"))
	        		res = "11101";
	        	else if(reg.equals("$fp"))
	        		res = "11110";
	        	else if(reg.equals("$ra"))
	        		res = "11111";

				return res; 
	        }
	    }
	    private class CodeButton implements ActionListener{
	        public void actionPerformed(ActionEvent e){
	            String[] row = text2.getText().split("\n");
	            String bopcode, bregs, bregt, bregd, bfunc, bsft,baddress, res = null;
	            String opcode = null,  regs= null, regt= null, regd= null, sft= null, func = null, address=null;
	            String imstr;
	            int imnum;
	            text1.setText("");
	            for(int i = 0; i<row.length; i++){
	            	if(row[i].equals(""))
	            		continue;
	            	row[i].replaceAll(" +", " ");
	            	row[i] = Long.toBinaryString(Long.parseLong(row[i], 16));
	            	while(row[i].length()<32)
	            		row[i] = "0"+row[i];
	            	bopcode = row[i].substring(0, 6);
	            	
	            	if(bopcode.equals("000000")== true) //R type
	            	{	            		
	            		bregs = row[i].substring(6, 11);
	            		bregt = row[i].substring(11, 16);
	        			bregd = row[i].substring(16, 21);
	        			bsft = row[i].substring(21,26);
	        			bfunc = row[i].substring(26, 32);
	        			
	        			imnum = Integer.parseInt(bsft, 2);
	        			sft = Integer.toString(imnum);
	        			
	            		regd = convert(bregd);
	            		regs = convert(bregs);
	            		regt = convert(bregt);
	            		
	            		if(bfunc.equals("100000")){
	            			opcode = "add";
	            			res = opcode+" "+regd+", "+regs+", "+regt;
	            		}
	            		if(bfunc.equals("100010")){
	            			opcode = "sub";
	            			res = opcode+" "+regd+", "+regs+", "+regt;
	            		}
	            		if(bfunc.equals("100100")){
	            			opcode = "and";
	            			res = opcode+" "+regd+", "+regs+", "+regt;
	            		}
	            		if(bfunc.equals("100101")){
	            			opcode = "or";
	            			res = opcode+" "+regd+", "+regs+", "+regt;
	            		}
	            		if(bfunc.equals("100110")){
	            			opcode = "xor";
	            			res = opcode+" "+regd+", "+regs+", "+regt;
	            		}
	            		if(bfunc.equals("100111")){
	            			opcode = "nor";
	            			res = opcode+" "+regd+", "+regs+", "+regt;
	            		}
	            		if(bfunc.equals("000011")){
	            			opcode = "sra";
	            			res = opcode+" "+regd+", "+regt+", "+sft;
	            		}
	            		if(bfunc.equals("101010")){
	            			opcode = "slt";
	            			res = opcode+" "+regd+", "+regs+", "+regt;
	            		}
	            		if(bfunc.equals("000000")){
	            			opcode = "sll";
	            			res = opcode+" "+regd+", "+regt+", "+ sft;
	            		}
	    				if(bfunc.equals("000010")){
	    					opcode = "srl";
	    					res = opcode+" "+regd+", "+regt+", "+ sft;
	    				}
	    				if(bfunc.equals("001000")){
	    					opcode = "jr";
	    					res = opcode+" "+regs;
	    				}
		        		
	            	}			    				

    				
	            	if(bopcode.equals("100011")||bopcode.equals("101011")||bopcode.equals("001000")||
	            			bopcode.equals("001111")||bopcode.equals("001101")||bopcode.equals("000100")||bopcode.equals("000101") == true) //I type
	            	{	            		
	            		bregs = row[i].substring(6, 11);
	            		bregt = row[i].substring(11, 16);
	        			baddress = row[i].substring(16,32);
	        			int tmp = 0;
	        			if(baddress.substring(0, 1).equals("1"))
	        				tmp = 65536;
	        			imnum = Integer.parseInt(baddress, 2);
	        			imnum-=tmp;
	        			address = Integer.toString(imnum);	 
	        		
	            		regs = convert(bregs);
	            		regt = convert(bregt);
	            		
	            		if(bopcode.equals("100011")){
	            			opcode = "lw";
	            			res = opcode+" "+regt+", "+address+"("+regs+")";
	            		}
	            		if(bopcode.equals("101011")){
	            			opcode = "sw";
	            			res = opcode+" "+regt+", "+address+"("+regs+")";
	            		}
	            		if(bopcode.equals("001000")){
	            			opcode = "addi";
	            			res = opcode+" "+regt+", "+regs+", "+address;
	            		}
	            		if(bopcode.equals("001101")){
	            			opcode = "ori";
	            			res = opcode+" "+regt+", "+regs+", "+address;
	            		}
	            		if(bopcode.equals("000100")){
	            			opcode = "beq";
	            			res = opcode+" "+regs+", "+regt+", "+address;
	            		}
	            		if(bopcode.equals("000101")){
	            			opcode = "bne";
	            			res = opcode+" "+regs+", "+regt+", "+address;
	            		}
	            		if(bopcode.equals("001111")){
	            			opcode = "lui";
	            			res = opcode+" "+regt+", "+address;
	            		}

	            	}	
	            	
	            	
	            	if(bopcode.equals("000010")||bopcode.equals("000011")== true) //J type
	            	{	            		

	        			baddress = row[i].substring(6,32);    			
	        			imnum = Integer.parseInt(baddress, 2);
	        			//imnum *= 4;
	        			address = Integer.toString(imnum);	        			
	            		
	            		if(bopcode.equals("000010")){
	            			opcode = "j";
	            			res = opcode+" "+address;
	            		}
	            		if(bopcode.equals("000011")){
	            			opcode = "jal";
	            			res = opcode+" "+address;
	            		}
		        		
	            	}			
    				     
	        		text1.append(res+" #PC= "+i*4+"\n");
	            }
	            //text2.append(row[i]+"yes\n");
	            
	            
	            
	            
	        }
	        public String convert(String reg){
	        	String res = null;
	        	if(reg.equals("00000"))
	        		res = "$zero";
	        	else if(reg.equals("00001"))
	        		res = "$at";
	        	else if(reg.equals("00010"))
	        		res = "$v0";
	        	else if(reg.equals("00011"))
	        		res = "$v1";
	        	else if(reg.equals("00100"))
	        		res = "$a0";
	        	else if(reg.equals("00101"))
	        		res = "$a1";
	        	else if(reg.equals("00110"))
	        		res = "$a2";
	        	else if(reg.equals("00111"))
	        		res = "$a3";
	        	else if(reg.equals("01000"))
	        		res = "$t0";
	        	else if(reg.equals("01001"))
	        		res = "$t1";
	        	else if(reg.equals("01010"))
	        		res = "$t2";
	        	else if(reg.equals("01011"))
	        		res = "$t3";
	        	else if(reg.equals("01100"))
	        		res = "$t4";
	        	else if(reg.equals("01101"))
	        		res = "$t5";
	        	else if(reg.equals("01110"))
	        		res = "$t6";
	        	else if(reg.equals("01111"))
	        		res = "$t7";
	        	else if(reg.equals("10000"))
	        		res = "$s0";
	        	else if(reg.equals("10001"))
	        		res = "$s1";
	        	else if(reg.equals("10010"))
	        		res = "$s2";
	        	else if(reg.equals("10011"))
	        		res = "$s3";
	        	else if(reg.equals("10100"))
	        		res = "$s4";
	        	else if(reg.equals("10101"))
	        		res = "$s5";
	        	else if(reg.equals("10110"))
	        		res = "$s6";
	        	else if(reg.equals("10111"))
	        		res = "$s7";
	        	else if(reg.equals("11000"))
	        		res = "$t8";
	        	else if(reg.equals("11001"))
	        		res = "$t9";
	        	else if(reg.equals("11010"))
	        		res = "$k0";
	        	else if(reg.equals("11011"))
	        		res = "$k1";
	        	else if(reg.equals("11100"))
	        		res = "$gp";
	        	else if(reg.equals("11101"))
	        		res = "$sp";
	        	else if(reg.equals("11110"))
	        		res = "$fp";
	        	else if(reg.equals("11111"))
	        		res = "$ra";

				return res; 
	        }
	    }
	    private class EndButton implements ActionListener{
	        public void actionPerformed(ActionEvent e){
	            String[] row = text1.getText().split("\n");
	            String[] word = null;
	            String opcode, regs, regt, regd;
	            int nums,numt,numd;
	            String imstr;
	            int imnum;
	            int a, b;
	            int pc, i;
	            int[] reg = new int[32];
	    		Map<String,String> map = new HashMap<String,String>();
	            
	            for(i = 0; i < 32; i++)
	            	reg[i] = 0;
	            reg[26] = 10000;
	            refresh(reg);
	            for(i = 0; i<row.length; i++){
	            	pc = i * 4;
	            	imstr = Integer.toString(pc);
		        	tpc.setText(imstr);  
	            	row[i].replaceAll(" +", " ");
	            	word = row[i].split("\\)|\\(| ,|, | |,");
	            	opcode = word[0];
	            	if(opcode.equals("xor")||opcode.equals("nor")||opcode.equals("add")||opcode.equals("sub")||opcode.equals("and")||opcode.equals("or")||opcode.equals("slt") == true) //R type with 3 reg
	            	{
	            		regd =word[1];
	            		regs = word[2];
	        			regt = word[3];
	        			numd = choose(regd);
	        			nums = choose(regs);
	        			numt = choose(regt);
	        			a = reg[nums];
	        			b = reg[numt];
	        			if(opcode.equals("xor")){
	            			reg[numd] = a^b;
	            			refresh(reg);
	            		}
	        			if(opcode.equals("nor")){
	            			reg[numd] = a|b;
	            			reg[numd] = ~reg[numd];
	            			refresh(reg);
	            		}
	            		if(opcode.equals("add")){
	            			reg[numd] = a+b;
	            			refresh(reg);
	            		}
	            		if(opcode.equals("sub")){
	            			reg[numd] = a-b;
	            			refresh(reg);
	            		}
	            		if(opcode.equals("and")){
	            			reg[numd] = a&b;
	            			refresh(reg);
	            		}
	            		if(opcode.equals("or")){
	            			reg[numd] = a|b;
            				refresh(reg);
	            		}
	            		if(opcode.equals("slt")){
	            			if(a<b)
	            				reg[numd] = 1;
	            			else
	            				reg[numd] = 0;
	            			refresh(reg);
	            		}	            			
	            	}
	            	
	            	if(opcode.equals("sll")||opcode.equals("srl")||opcode.equals("sra")){
        				regd = word[1];
        				regt = word[2];
        				imstr = word[3];
        				imnum = Integer.valueOf(imstr);        				
        				numd = choose(regd);
	        			numt = choose(regt);
	        			b = reg[numt];
	            		if(opcode.equals("sll")){
	            			b = b<<imnum;
	            			reg[numd] = b;
	            			refresh(reg);
	            		}	    					
	    				if(opcode.equals("srl")){
	    					b = b>>>imnum;
	            			reg[numd] = b;
	            			refresh(reg);
	    				}
	    				if(opcode.equals("sra")){
	    					b = b>>imnum;
	            			reg[numd] = b;
	            			refresh(reg);
	    				}
	    					
	            	}	    				
    				if(opcode.equals("jr")){
    					regs = word[1];
    					nums = choose(regs);    					
    					i = reg[nums]/4-1;
    					continue;
    				}
    					   				
    				if(opcode.equals("addi")||opcode.equals("ori") == true) //i type 1
	            	{
    					
	            		regt = word[1];
	        			regs = word[2]; 
	            		imstr = word[3];
        				imnum = Integer.valueOf(imstr);
	        			numt = choose(regt);
	        			nums = choose(regs);
	        			a = reg[nums];
	            		if(opcode.equals("addi")){
	            			reg[numt] = a+imnum;
	            			refresh(reg);
	            		}	    					
	    				if(opcode.equals("ori")){
	            			reg[numt] = a|imnum;
	            			refresh(reg);
	    				}


	            	}
    				if(opcode.equals("lui") == true) //i type 1
	            	{
	            		regt = word[1];
	            		imstr = word[2];
	       				imnum = Integer.valueOf(imstr);
	       				imnum*=65536;
	        			numt = choose(regt); 					
	            		reg[numt] = imnum;

 
	            		refresh(reg);
	    				}


    				if(opcode.equals("beq")||opcode.equals("bne") == true) //i type 1
	            	{
    					
    					regs = word[1];
	        			regt = word[2]; 
	            		imstr = word[3];
        				imnum = Integer.valueOf(imstr);
	        			nums = choose(regs);
	        			numt = choose(regt);
	        			a = reg[nums];
	        			b = reg[numt];
	            		if(opcode.equals("beq")){
	            			if(a == b){
	            				i = i + imnum;
	            				continue;
	            			}
	            		}
	            		if(opcode.equals("bne")){
	            			if(a != b){
	            				i = i + imnum;
	            				continue;
	            			}
	            		}
	            			
	            	}
    				if(opcode.equals("lw")||opcode.equals("sw") == true) //i type 1
	            	{
    					String address;
    					String value;
    					regt = word[1];
	        			regs = word[3]; 
	        			nums = choose(regs);
	        			numt = choose(regt);
	            		imstr = word[2];
        				imnum = Integer.valueOf(imstr);
        				address = Integer.toString(imnum+nums);
        				
        				if(opcode.equals("sw")){
        					value = Integer.toString(reg[numt]);
        					map.put(address, value);
        				}
        				if(opcode.equals("lw")){
        					value = map.get(address);
        					reg[numt] = Integer.valueOf(value);
        					refresh(reg);
        				}

	            	}
    				if(opcode.equals("j")||opcode.equals("jal") == true) //i type 1
	            	{
	            		imstr = word[1];
        				imnum = Integer.valueOf(imstr);
        				if(opcode.equals("j")){
        					i = imnum - 1;
        				}
        				if(opcode.equals("jal")){
        					reg[28] = pc+4;
        					refresh(reg);
        					i = imnum - 1;
        				}
        				
	            	}  
	        
	            }
	            pc = i * 4;
            	imstr = Integer.toString(pc);
	        	tpc.setText(imstr);  
	            
	    }

	        public int choose(String reg){
	        	int res = -1;
	        	if(reg.equals("$zero"))
	        		res = 0;
	        	else if(reg.equals("$v0"))
	        		res = 1;
	        	else if(reg.equals("$v1"))
	        		res = 2;
	        	else if(reg.equals("$a0"))
	        		res = 3;
	        	else if(reg.equals("$a1"))
	        		res = 4;
	        	else if(reg.equals("$a2"))
	        		res = 5;
	        	else if(reg.equals("$a3"))
	        		res = 6;
	        	else if(reg.equals("$t0"))
	        		res = 7;
	        	else if(reg.equals("$t1"))
	        		res = 8;
	        	else if(reg.equals("$t2"))
	        		res = 9;
	        	else if(reg.equals("$t3"))
	        		res = 10;
	        	else if(reg.equals("$t4"))
	        		res = 11;
	        	else if(reg.equals("$t5"))
	        		res = 12;
	        	else if(reg.equals("$t6"))
	        		res = 13;
	        	else if(reg.equals("$t7"))
	        		res = 14;
	        	else if(reg.equals("$s0"))
	        		res = 17;
	        	else if(reg.equals("$s1"))
	        		res = 18;
	        	else if(reg.equals("$s2"))
	        		res = 19;
	        	else if(reg.equals("$s3"))
	        		res = 20;
	        	else if(reg.equals("$s4"))
	        		res = 21;
	        	else if(reg.equals("$s5"))
	        		res = 22;
	        	else if(reg.equals("$s6"))
	        		res = 23;
	        	else if(reg.equals("$s7"))
	        		res = 24;
	        	else if(reg.equals("$t8"))
	        		res = 15;
	        	else if(reg.equals("$t9"))
	        		res = 16;
	        	else if(reg.equals("$gp"))
	        		res = 25;
	        	else if(reg.equals("$sp"))
	        		res = 26;
	        	else if(reg.equals("$fp"))
	        		res = 27;
	        	else if(reg.equals("$ra"))
	        		res = 28;
	        	else if(reg.equals("$at"))
	        		res = 29;
	        	else if(reg.equals("$k0"))
	        		res = 30;
	        	else if(reg.equals("$k1"))
	        		res = 31;

				return res; 
	        }
	        public void refresh(int[] reg){
	        	String s;
	        	s = Integer.toString(reg[0]);
	        	tzero.setText(s);  
	        	s = Integer.toString(reg[1]);
	        	tv0.setText(s);  
	        	s = Integer.toString(reg[2]);
	        	tv1.setText(s);
	        	s = Integer.toString(reg[3]);
	        	ta0.setText(s);  
	        	s = Integer.toString(reg[4]);
	        	ta1.setText(s);  
	        	s = Integer.toString(reg[5]);
	        	ta2.setText(s);  
	        	s = Integer.toString(reg[6]);
	        	ta3.setText(s);  
	        	s = Integer.toString(reg[7]);
	        	tt0.setText(s);  
	        	s = Integer.toString(reg[8]);
	        	tt1.setText(s);  
	        	s = Integer.toString(reg[9]);
	        	tt2.setText(s); 
	        	s = Integer.toString(reg[10]);
	        	tt3.setText(s);  
	        	s = Integer.toString(reg[11]);
	        	tt4.setText(s);  
	        	s = Integer.toString(reg[12]);
	        	tt5.setText(s);  
	        	s = Integer.toString(reg[13]);
	        	tt6.setText(s);
	        	s = Integer.toString(reg[14]);
	        	tt7.setText(s); 
	        	s = Integer.toString(reg[15]);
	        	tt8.setText(s);  
	        	s = Integer.toString(reg[16]);
	        	tt9.setText(s);  
	        	s = Integer.toString(reg[17]);
	        	ts0.setText(s);
	        	s = Integer.toString(reg[18]);
	        	ts1.setText(s); 
	        	s = Integer.toString(reg[19]);
	        	ts2.setText(s);  
	        	s = Integer.toString(reg[20]);
	        	ts3.setText(s);  
	        	s = Integer.toString(reg[21]);
	        	ts4.setText(s); 
	        	s = Integer.toString(reg[22]);
	        	ts5.setText(s);
	        	s = Integer.toString(reg[23]);
	        	ts6.setText(s);  
	        	s = Integer.toString(reg[24]);
	        	ts7.setText(s); 
	        	s = Integer.toString(reg[25]);
	        	tgp.setText(s);  
	        	s = Integer.toString(reg[26]);
	        	tsp.setText(s);  
	        	s = Integer.toString(reg[27]);
	        	tfp.setText(s);  
	        	s = Integer.toString(reg[28]);
	        	tra.setText(s);  
	        	
	    
	        }	        
	    }

	    private class ResetButton implements ActionListener{
	        public void actionPerformed(ActionEvent e){

	            for(int j = 0; j < 32; j++)
	            	reg[j] = 0;
	            reg[26] = 10000;
	            flag = 0;
	            refresh(reg);
	            pc = 0;
	            i = 0;
            	imstr = Integer.toString(pc);
	        	tpc.setText(imstr);  
	        }
	        
	        public void refresh(int[] reg){
	        	String s;
	        	s = Integer.toString(reg[0]);
	        	tzero.setText(s);  
	        	s = Integer.toString(reg[1]);
	        	tv0.setText(s);  
	        	s = Integer.toString(reg[2]);
	        	tv1.setText(s);
	        	s = Integer.toString(reg[3]);
	        	ta0.setText(s);  
	        	s = Integer.toString(reg[4]);
	        	ta1.setText(s);  
	        	s = Integer.toString(reg[5]);
	        	ta2.setText(s);  
	        	s = Integer.toString(reg[6]);
	        	ta3.setText(s);  
	        	s = Integer.toString(reg[7]);
	        	tt0.setText(s);  
	        	s = Integer.toString(reg[8]);
	        	tt1.setText(s);  
	        	s = Integer.toString(reg[9]);
	        	tt2.setText(s); 
	        	s = Integer.toString(reg[10]);
	        	tt3.setText(s);  
	        	s = Integer.toString(reg[11]);
	        	tt4.setText(s);  
	        	s = Integer.toString(reg[12]);
	        	tt5.setText(s);  
	        	s = Integer.toString(reg[13]);
	        	tt6.setText(s);
	        	s = Integer.toString(reg[14]);
	        	tt7.setText(s); 
	        	s = Integer.toString(reg[15]);
	        	tt8.setText(s);  
	        	s = Integer.toString(reg[16]);
	        	tt9.setText(s);  
	        	s = Integer.toString(reg[17]);
	        	ts0.setText(s);
	        	s = Integer.toString(reg[18]);
	        	ts1.setText(s); 
	        	s = Integer.toString(reg[19]);
	        	ts2.setText(s);  
	        	s = Integer.toString(reg[20]);
	        	ts3.setText(s);  
	        	s = Integer.toString(reg[21]);
	        	ts4.setText(s); 
	        	s = Integer.toString(reg[22]);
	        	ts5.setText(s);
	        	s = Integer.toString(reg[23]);
	        	ts6.setText(s);  
	        	s = Integer.toString(reg[24]);
	        	ts7.setText(s); 
	        	s = Integer.toString(reg[25]);
	        	tgp.setText(s);  
	        	s = Integer.toString(reg[26]);
	        	tsp.setText(s);  
	        	s = Integer.toString(reg[27]);
	        	tfp.setText(s);  
	        	s = Integer.toString(reg[28]);
	        	tra.setText(s);  
	        	
	    
	        }	        
	    }
	    private class DoButton implements ActionListener{
	        public void actionPerformed(ActionEvent e){
	        	row = text1.getText().split("\n");
	    		if(flag == 0){
	            for(int j = 0; j < 32; j++)
	            	reg[j] = 0;
	            reg[26] = 10000;
	            flag = 1;
	    		}
	    			if(i < row.length){
	            	pc = i * 4;
	            	imstr = Integer.toString(pc);
		        	tpc.setText(imstr);  
	            	row[i].replaceAll(" +", " ");
	            	word = row[i].split("\\)|\\(| ,|, | |,");
	            	opcode = word[0];
	            	if(opcode.equals("nor")||opcode.equals("xor")||opcode.equals("add")||opcode.equals("sub")||opcode.equals("and")||opcode.equals("or")||opcode.equals("slt") == true) //R type with 3 reg
	            	{
	            		regd =word[1];
	            		regs = word[2];
	        			regt = word[3];
	        			numd = choose(regd);
	        			nums = choose(regs);
	        			numt = choose(regt);
	        			a = reg[nums];
	        			b = reg[numt];
	            		if(opcode.equals("add")){
	            			reg[numd] = a+b;
	            			refresh(reg);
	            		}
	            		if(opcode.equals("xor")){
	            			reg[numd] = a^b;
	            			refresh(reg);
	            		}
	        			if(opcode.equals("nor")){
	            			reg[numd] = a|b;
	            			reg[numd] = ~reg[numd];
	            			refresh(reg);
	            		}
	            		if(opcode.equals("sub")){
	            			reg[numd] = a-b;
	            			refresh(reg);
	            		}
	            		if(opcode.equals("and")){
	            			reg[numd] = a&b;
	            			refresh(reg);
	            		}
	            		if(opcode.equals("or")){
	            			reg[numd] = a|b;
            				refresh(reg);
	            		}
	            		if(opcode.equals("slt")){
	            			if(a<b)
	            				reg[numd] = 1;
	            			else
	            				reg[numd] = 0;
	            			refresh(reg);
	            		}	            			
	            	}
	            	
	            	if(opcode.equals("sll")||opcode.equals("srl")||opcode.equals("sra")){
        				regd = word[1];
        				regt = word[2];
        				imstr = word[3];
        				imnum = Integer.valueOf(imstr);        				
        				numd = choose(regd);
	        			numt = choose(regt);
	        			b = reg[numt];
	            		if(opcode.equals("sll")){
	            			b = b<<imnum;
	            			reg[numd] = b;
	            			refresh(reg);
	            		}	    					
	    				if(opcode.equals("srl")){
	    					b = b>>>imnum;
	            			reg[numd] = b;
	            			refresh(reg);
	    				}
	    				if(opcode.equals("sra")){
	    					b = b>>imnum;
	            			reg[numd] = b;
	            			refresh(reg);
	    				}	
	            	}	    				
    				if(opcode.equals("jr")){
    					regs = word[1];
    					nums = choose(regs);    					
    					i = reg[nums]/4-1;
    				}
    					   				
    				if(opcode.equals("addi")||opcode.equals("ori") == true) //i type 1
	            	{
    					
	            		regt = word[1];
	        			regs = word[2]; 
	            		imstr = word[3];
        				imnum = Integer.valueOf(imstr);
	        			numt = choose(regt);
	        			nums = choose(regs);
	        			a = reg[nums];
	            		if(opcode.equals("addi")){
	            			reg[numt] = a+imnum;
	            			refresh(reg);
	            		}	    					
	    				if(opcode.equals("ori")){
	            			reg[numt] = a|imnum;
	            			refresh(reg);
	    				}


	            	}
    				if(opcode.equals("lui") == true) //i type 1
	            	{
	            		regt = word[1];
	            		imstr = word[2];
	       				imnum = Integer.valueOf(imstr);
	       				imnum*=65536;
	        			numt = choose(regt); 					
	            		reg[numt] = imnum;
	            		refresh(reg);
	    				}

    				if(opcode.equals("beq")||opcode.equals("bne") == true) //i type 1
	            	{
    					
    					regs = word[1];
	        			regt = word[2]; 
	            		imstr = word[3];
        				imnum = Integer.valueOf(imstr);
	        			nums = choose(regs);
	        			numt = choose(regt);
	        			a = reg[nums];
	        			b = reg[numt];
	            		if(opcode.equals("beq")){
	            			if(a == b){
	            				i = i + imnum;
	            			}
	            		}
	            		if(opcode.equals("bne")){
	            			if(a != b){
	            				i = i + imnum;
	            			}
	            		}
	            			
	            	}
    				if(opcode.equals("lw")||opcode.equals("sw") == true) //i type 1
	            	{
    					String address;
    					String value;
    					regt = word[1];
	        			regs = word[3]; 
	        			nums = choose(regs);
	        			numt = choose(regt);
	            		imstr = word[2];
        				imnum = Integer.valueOf(imstr);
        				address = Integer.toString(imnum+nums);
        				
        				if(opcode.equals("sw")){
        					value = Integer.toString(reg[numt]);
        					map.put(address, value);
        				}
        				if(opcode.equals("lw")){
        					value = map.get(address);
        					reg[numt] = Integer.valueOf(value);
        					refresh(reg);
        				}

	            	}
    				if(opcode.equals("j")||opcode.equals("jal") == true) //i type 1
	            	{
	            		imstr = word[1];
        				imnum = Integer.valueOf(imstr);
        				if(opcode.equals("j")){
        					i = imnum - 1;
        				}
        				if(opcode.equals("jal")){
        					reg[28] = pc+4;
        					refresh(reg);
        					i = imnum - 1;
        				}
        				
	            	} 
	            i = i+1;
	    			}
	    			pc = i * 4;
	            	imstr = Integer.toString(pc);
		        	tpc.setText(imstr);  
	        }
	        public int choose(String reg){
	        	int res = -1;
	        	if(reg.equals("$zero"))
	        		res = 0;
	        	else if(reg.equals("$v0"))
	        		res = 1;
	        	else if(reg.equals("$v1"))
	        		res = 2;
	        	else if(reg.equals("$a0"))
	        		res = 3;
	        	else if(reg.equals("$a1"))
	        		res = 4;
	        	else if(reg.equals("$a2"))
	        		res = 5;
	        	else if(reg.equals("$a3"))
	        		res = 6;
	        	else if(reg.equals("$t0"))
	        		res = 7;
	        	else if(reg.equals("$t1"))
	        		res = 8;
	        	else if(reg.equals("$t2"))
	        		res = 9;
	        	else if(reg.equals("$t3"))
	        		res = 10;
	        	else if(reg.equals("$t4"))
	        		res = 11;
	        	else if(reg.equals("$t5"))
	        		res = 12;
	        	else if(reg.equals("$t6"))
	        		res = 13;
	        	else if(reg.equals("$t7"))
	        		res = 14;
	        	else if(reg.equals("$s0"))
	        		res = 17;
	        	else if(reg.equals("$s1"))
	        		res = 18;
	        	else if(reg.equals("$s2"))
	        		res = 19;
	        	else if(reg.equals("$s3"))
	        		res = 20;
	        	else if(reg.equals("$s4"))
	        		res = 21;
	        	else if(reg.equals("$s5"))
	        		res = 22;
	        	else if(reg.equals("$s6"))
	        		res = 23;
	        	else if(reg.equals("$s7"))
	        		res = 24;
	        	else if(reg.equals("$t8"))
	        		res = 15;
	        	else if(reg.equals("$t9"))
	        		res = 16;
	        	else if(reg.equals("$gp"))
	        		res = 25;
	        	else if(reg.equals("$sp"))
	        		res = 26;
	        	else if(reg.equals("$fp"))
	        		res = 27;
	        	else if(reg.equals("$ra"))
	        		res = 28;
	        	else if(reg.equals("$at"))
	        		res = 29;
	        	else if(reg.equals("$k0"))
	        		res = 30;
	        	else if(reg.equals("$k1"))
	        		res = 31;

				return res; 
	        }
	        public void refresh(int[] reg){
	        	String s;
	        	s = Integer.toString(reg[0]);
	        	tzero.setText(s);  
	        	s = Integer.toString(reg[1]);
	        	tv0.setText(s);  
	        	s = Integer.toString(reg[2]);
	        	tv1.setText(s);
	        	s = Integer.toString(reg[3]);
	        	ta0.setText(s);  
	        	s = Integer.toString(reg[4]);
	        	ta1.setText(s);  
	        	s = Integer.toString(reg[5]);
	        	ta2.setText(s);  
	        	s = Integer.toString(reg[6]);
	        	ta3.setText(s);  
	        	s = Integer.toString(reg[7]);
	        	tt0.setText(s);  
	        	s = Integer.toString(reg[8]);
	        	tt1.setText(s);  
	        	s = Integer.toString(reg[9]);
	        	tt2.setText(s); 
	        	s = Integer.toString(reg[10]);
	        	tt3.setText(s);  
	        	s = Integer.toString(reg[11]);
	        	tt4.setText(s);  
	        	s = Integer.toString(reg[12]);
	        	tt5.setText(s);  
	        	s = Integer.toString(reg[13]);
	        	tt6.setText(s);
	        	s = Integer.toString(reg[14]);
	        	tt7.setText(s); 
	        	s = Integer.toString(reg[15]);
	        	tt8.setText(s);  
	        	s = Integer.toString(reg[16]);
	        	tt9.setText(s);  
	        	s = Integer.toString(reg[17]);
	        	ts0.setText(s);
	        	s = Integer.toString(reg[18]);
	        	ts1.setText(s); 
	        	s = Integer.toString(reg[19]);
	        	ts2.setText(s);  
	        	s = Integer.toString(reg[20]);
	        	ts3.setText(s);  
	        	s = Integer.toString(reg[21]);
	        	ts4.setText(s); 
	        	s = Integer.toString(reg[22]);
	        	ts5.setText(s);
	        	s = Integer.toString(reg[23]);
	        	ts6.setText(s);  
	        	s = Integer.toString(reg[24]);
	        	ts7.setText(s); 
	        	s = Integer.toString(reg[25]);
	        	tgp.setText(s);  
	        	s = Integer.toString(reg[26]);
	        	tsp.setText(s);  
	        	s = Integer.toString(reg[27]);
	        	tfp.setText(s);  
	        	s = Integer.toString(reg[28]);
	        	tra.setText(s);  
	        	
	    
	        }	        
	    }
	   /* private JTextArea getTextArea1(){
	        if(text1==null){
	            text1 = new JTextArea();
	            text1.setBounds(96,49,320,200);
	        }
	        return text1;
	    }
	    private JTextArea getTextArea2(){
	    	if(text2 == null){
	    		text2 = new JTextArea();
	    		text2.setBounds(96, 300, 320, 200);
	    }
	    return text2;
	}*/
	    private JLabel getLabel0(){
	        if(label0==null){
	            label0 = new JLabel();
	            label0.setBounds(510,20,53,18);
	            label0.setText("$zero");
	            label0.setToolTipText("$zero");
	        }
	        return label0;
	    }	   
	    private JLabel getLabel1(){
	        if(label1==null){
	            label1 = new JLabel();
	            label1.setBounds(510,40,53,18);
	            label1.setText("$v0");
	            label1.setToolTipText("$v0");
	        }
	        return label1;
	    }
	    private JLabel getLabel2(){
	        if(label2==null){
	            label2 = new JLabel();
	            label2.setBounds(510,60,53,18);
	            label2.setText("$v1");
	            label2.setToolTipText("$v1");
	        }
	        return label2;
	    }
	    private JLabel getLabel3(){
	        if(label3==null){
	            label3 = new JLabel();
	            label3.setBounds(510,80,53,18);
	            label3.setText("$a0");
	            label3.setToolTipText("$a0");
	        }
	        return label3;
	    }
	    private JLabel getLabel4(){
	        if(label4==null){
	            label4 = new JLabel();
	            label4.setBounds(510,100,53,18);
	            label4.setText("$a1");
	            label4.setToolTipText("$a1");
	        }
	        return label4;
	    }
	    private JLabel getLabel5(){
	        if(label5==null){
	            label5 = new JLabel();
	            label5.setBounds(510,120,53,18);
	            label5.setText("$a2");
	            label5.setToolTipText("$a2");
	        }
	        return label5;
	    }
	    private JLabel getLabel6(){
	        if(label6==null){
	            label6 = new JLabel();
	            label6.setBounds(510,140,53,18);
	            label6.setText("$a3");
	            label6.setToolTipText("$a3");
	        }
	        return label6;
	    }
	    private JLabel getLabel7(){
	        if(label7==null){
	            label7 = new JLabel();
	            label7.setBounds(510,160,53,18);
	            label7.setText("$t0");
	            label7.setToolTipText("$t0");
	        }
	        return label7;
	    }
	    private JLabel getLabel8(){
	        if(label8==null){
	            label8 = new JLabel();
	            label8.setBounds(510,180,53,18);
	            label8.setText("$t1");
	            label8.setToolTipText("$t1");
	        }
	        return label8;
	    }
	    private JLabel getLabel9(){
	        if(label9==null){
	            label9 = new JLabel();
	            label9.setBounds(510,200,53,18);
	            label9.setText("$t2");
	            label9.setToolTipText("$t2");
	        }
	        return label9;
	    }
	    private JLabel getLabel10(){
	        if(label10==null){
	            label10 = new JLabel();
	            label10.setBounds(510,220,53,18);
	            label10.setText("$t3");
	            label10.setToolTipText("$t3");
	        }
	        return label10;
	    }
	    private JLabel getLabel11(){
	        if(label11==null){
	            label11 = new JLabel();
	            label11.setBounds(510,240,53,18);
	            label11.setText("$t4");
	            label11.setToolTipText("$t4");
	        }
	        return label11;
	    }
	    private JLabel getLabel12(){
	        if(label12==null){
	            label12 = new JLabel();
	            label12.setBounds(510,260,53,18);
	            label12.setText("$t5");
	            label12.setToolTipText("$t5");
	        }
	        return label12;
	    }
	    private JLabel getLabel13(){
	        if(label13==null){
	            label13 = new JLabel();
	            label13.setBounds(510,280,53,18);
	            label13.setText("$t6");
	            label13.setToolTipText("$t6");
	        }
	        return label13;
	    }
	    private JLabel getLabel14(){
	        if(label14==null){
	            label14 = new JLabel();
	            label14.setBounds(510,300,53,18);
	            label14.setText("$t7");
	            label14.setToolTipText("$t7");
	        }
	        return label14;
	    }
	    private JLabel getLabel15(){
	        if(label15==null){
	            label15 = new JLabel();
	            label15.setBounds(510,320,53,18);
	            label15.setText("$t8");
	            label15.setToolTipText("$t8");
	        }
	        return label15;
	    }
	    private JLabel getLabel16(){
	        if(label16==null){
	            label16 = new JLabel();
	            label16.setBounds(510,340,53,18);
	            label16.setText("$t9");
	            label16.setToolTipText("$t9");
	        }
	        return label16;
	    }
	    private JLabel getLabel17(){
	        if(label17==null){
	            label17 = new JLabel();
	            label17.setBounds(510,360,53,18);
	            label17.setText("$s0");
	            label17.setToolTipText("$s0");
	        }
	        return label17;
	    }
	    private JLabel getLabel18(){
	        if(label18==null){
	            label18 = new JLabel();
	            label18.setBounds(510,380,53,18);
	            label18.setText("$s1");
	            label18.setToolTipText("$s1");
	        }
	        return label18;
	    }
	    private JLabel getLabel19(){
	        if(label19==null){
	            label19 = new JLabel();
	            label19.setBounds(510,400,53,18);
	            label19.setText("$s2");
	            label19.setToolTipText("$s2");
	        }
	        return label19;
	    }
	    private JLabel getLabel20(){
	        if(label20==null){
	            label20 = new JLabel();
	            label20.setBounds(510,420,53,18);
	            label20.setText("$s3");
	            label20.setToolTipText("$s3");
	        }
	        return label20;
	    }
	    private JLabel getLabel21(){
	        if(label21==null){
	            label21 = new JLabel();
	            label21.setBounds(510,440,53,18);
	            label21.setText("$s4");
	            label21.setToolTipText("$s4");
	        }
	        return label21;
	    }
	    private JLabel getLabel22(){
	        if(label22==null){
	            label22 = new JLabel();
	            label22.setBounds(510,460,53,18);
	            label22.setText("$s5");
	            label22.setToolTipText("$s5");
	        }
	        return label22;
	    }
	    private JLabel getLabel23(){
	        if(label23==null){
	            label23 = new JLabel();
	            label23.setBounds(510,480,53,18);
	            label23.setText("$s6");
	            label23.setToolTipText("$s6");
	        }
	        return label23;
	    }
	    private JLabel getLabel24(){
	        if(label24==null){
	            label24 = new JLabel();
	            label24.setBounds(510,500,53,18);
	            label24.setText("$s7");
	            label24.setToolTipText("$s7");
	        }
	        return label24;
	    }
	    private JLabel getLabel25(){
	        if(label25==null){
	            label25 = new JLabel();
	            label25.setBounds(510,520,53,18);
	            label25.setText("$gp");
	            label25.setToolTipText("$gp");
	        }
	        return label25;
	    }
	    private JLabel getLabel26(){
	        if(label26==null){
	            label26 = new JLabel();
	            label26.setBounds(510,540,53,18);
	            label26.setText("$sp");
	            label26.setToolTipText("$sp");
	        }
	        return label26;
	    }
	    private JLabel getLabel27(){
	        if(label27==null){
	            label27 = new JLabel();
	            label27.setBounds(510,560,53,18);
	            label27.setText("$fp");
	            label27.setToolTipText("$fp");
	        }
	        return label27;
	    }
	    private JLabel getLabel28(){
	        if(label28==null){
	            label28 = new JLabel();
	            label28.setBounds(510,580,53,18);
	            label28.setText("$ra");
	            label28.setToolTipText("$ra");
	        }
	        return label28;
	    }
	    private JLabel getLabelpc(){
	        if(labelpc==null){
	            labelpc = new JLabel();
	            labelpc.setBounds(510,600,53,18);
	            labelpc.setText("PC");
	            labelpc.setToolTipText("PC");
	        }
	        return labelpc;
	    }
	    private JTextField getTextField0(){
	        if(tzero==null){
	            tzero = new JTextField();
	            tzero.setBounds(560,20,100,18);
	            tzero.setText("zero");
	        }
	        return tzero;
	    }
	    private JTextField getTextField1(){
	        if(tv0==null){
	            tv0 = new JTextField();
	            tv0.setBounds(560,40,100,18);
	            tv0.setText("v0");
	        }
	        return tv0;
	    }
	    private JTextField getTextField2(){
	        if(tv1==null){
	            tv1 = new JTextField();
	            tv1.setBounds(560,60,100,18);
	            tv1.setText("v1");
	        }
	        return tv1;
	    }
	    private JTextField getTextField3(){
	        if(ta0==null){
	            ta0 = new JTextField();
	            ta0.setBounds(560,80,100,18);
	            ta0.setText("a0");
	        }
	        return ta0;
	    }
	    private JTextField getTextField4(){
	        if(ta1==null){
	            ta1 = new JTextField();
	            ta1.setBounds(560,100,100,18);
	            ta1.setText("a1");
	        }
	        return ta1;
	    }
	    private JTextField getTextField5(){
	        if(ta2==null){
	            ta2 = new JTextField();
	            ta2.setBounds(560,120,100,18);
	            ta2.setText("a2");
	        }
	        return ta2;
	    }
	    private JTextField getTextField6(){
	        if(ta3==null){
	            ta3 = new JTextField();
	            ta3.setBounds(560,140,100,18);
	            ta3.setText("a3");
	        }
	        return ta3;
	    }
	    private JTextField getTextField7(){
	        if(tt0==null){
	            tt0 = new JTextField();
	            tt0.setBounds(560,160,100,18);
	            tt0.setText("t0");
	        }
	        return tt0;
	    }
	    private JTextField getTextField8(){
	        if(tt1==null){
	            tt1 = new JTextField();
	            tt1.setBounds(560,180,100,18);
	            tt1.setText("t1");
	        }
	        return tt1;
	    }
	    private JTextField getTextField9(){
	        if(tt2==null){
	            tt2 = new JTextField();
	            tt2.setBounds(560,200,100,18);
	            tt2.setText("t2");
	        }
	        return tt2;
	    }
	    private JTextField getTextField10(){
	        if(tt3==null){
	            tt3 = new JTextField();
	            tt3.setBounds(560,220,100,18);
	            tt3.setText("t3");
	        }
	        return tt3;
	    }
	    private JTextField getTextField11(){
	        if(tt4==null){
	            tt4 = new JTextField();
	            tt4.setBounds(560,240,100,18);
	            tt4.setText("t4");
	        }
	        return tt4;
	    }
	    private JTextField getTextField12(){
	        if(tt5==null){
	            tt5 = new JTextField();
	            tt5.setBounds(560,260,100,18);
	            tt5.setText("t5");
	        }
	        return tt5;
	    }
	    private JTextField getTextField13(){
	        if(tt6==null){
	            tt6 = new JTextField();
	            tt6.setBounds(560,280,100,18);
	            tt6.setText("t6");
	        }
	        return tt6;
	    }
	    private JTextField getTextField14(){
	        if(tt7==null){
	            tt7 = new JTextField();
	            tt7.setBounds(560,300,100,18);
	            tt7.setText("t7");
	        }
	        return tt7;
	    }
	    private JTextField getTextField15(){
	        if(tt8==null){
	            tt8 = new JTextField();
	            tt8.setBounds(560,320,100,18);
	            tt8.setText("t8");
	        }
	        return tt8;
	    }
	    private JTextField getTextField16(){
	        if(tt9==null){
	            tt9 = new JTextField();
	            tt9.setBounds(560,340,100,18);
	            tt9.setText("t9");
	        }
	        return tt9;
	    }
	    private JTextField getTextField17(){
	        if(ts0==null){
	            ts0 = new JTextField();
	            ts0.setBounds(560,360,100,18);
	            ts0.setText("s0");
	        }
	        return ts0;
	    }
	    private JTextField getTextField18(){
	        if(ts1==null){
	            ts1 = new JTextField();
	            ts1.setBounds(560,380,100,18);
	            ts1.setText("s1");
	        }
	        return ts1;
	    }
	    private JTextField getTextField19(){
	        if(ts2==null){
	            ts2 = new JTextField();
	            ts2.setBounds(560,400,100,18);
	            ts2.setText("s2");
	        }
	        return ts2;
	    }
	    private JTextField getTextField20(){
	        if(ts3==null){
	            ts3 = new JTextField();
	            ts3.setBounds(560,420,100,18);
	            ts3.setText("s3");
	        }
	        return ts3;
	    }
	    private JTextField getTextField21(){
	        if(ts4==null){
	            ts4 = new JTextField();
	            ts4.setBounds(560,440,100,18);
	            ts4.setText("s4");
	        }
	        return ts4;
	    }
	    private JTextField getTextField22(){
	        if(ts5==null){
	            ts5 = new JTextField();
	            ts5.setBounds(560,460,100,18);
	            ts5.setText("s5");
	        }
	        return ts5;
	    }
	    private JTextField getTextField23(){
	        if(ts6==null){
	            ts6 = new JTextField();
	            ts6.setBounds(560,480,100,18);
	            ts6.setText("s6");
	        }
	        return ts6;
	    }
	    private JTextField getTextField24(){
	        if(ts7==null){
	            ts7 = new JTextField();
	            ts7.setBounds(560,500,100,18);
	            ts7.setText("s7");
	        }
	        return ts7;
	    }
	    private JTextField getTextField25(){
	        if(tgp==null){
	            tgp = new JTextField();
	            tgp.setBounds(560,520,100,18);
	            tgp.setText("gp");
	        }
	        return tgp;
	    }
	    private JTextField getTextField26(){
	        if(tsp==null){
	            tsp = new JTextField();
	            tsp.setBounds(560,540,100,18);
	            tsp.setText("sp");
	        }
	        return tsp;
	    }
	    private JTextField getTextField27(){
	        if(tfp==null){
	            tfp = new JTextField();
	            tfp.setBounds(560,560,100,18);
	            tfp.setText("fp");
	        }
	        return tfp;
	    }
	    private JTextField getTextField28(){
	        if(tra==null){
	            tra = new JTextField();
	            tra.setBounds(560,580,100,18);
	            tra.setText("ra");
	        }
	        return tra;
	    }
	    private JTextField getTextFieldpc(){
	        if(tpc==null){
	            tpc = new JTextField();
	            tpc.setBounds(560,600,100,18);
	            tpc.setText("PC=0");
	        }
	        return tpc;
	    }
	    
}
