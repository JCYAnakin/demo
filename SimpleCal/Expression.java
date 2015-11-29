import java.util.*;

/*issue:
&
(1+
(+1
((1
1))
((1+1))
2+1*3-2/1+3%2 = 4
1/3%3 = 0
()()
 1   + 1
1+(-2):no num1, but follows a +/-
-(8%3)*2+1
-(2*4)+(-2)*3
 */
public class Expression
{
    public static boolean checkSymbolsValid(String input)
    {
        for(int i = 0; i < input.length(); i++)
        {
            if(!(input.charAt(i) == ' '||input.charAt(i) == '+'||
                    input.charAt(i) == '-'||input.charAt(i) == '*'||
                    input.charAt(i) == '/'||input.charAt(i) == '%'||
                    input.charAt(i) == '('||input.charAt(i) == ')'||
                    input.charAt(i) >= '0'&&input.charAt(i) <= '9'))
                return false;
        }
        return true;
    }
    public static String normalize(String input)
    {
        input = " "+input;
        input = input.replaceAll("\\+-","-");
        input = input.replaceAll("\\+"," + ");
        input = input.replaceAll("-"," - ");
        input = input.replaceAll("\\*"," * ");
        input = input.replaceAll("/"," / ");
        input = input.replaceAll("%"," % ");
        input = input.replaceAll("\\("," ( ");
        input = input.replaceAll("\\)"," ) ");
        String res = null;
        res = input.replaceAll(" +"," ");
        if(res.charAt(1) == '-')
        {
            res = " 0"+res;
        }

        return res;
    }
    public static double math(String[] a)
    {
        try {
            double num1 = Double.parseDouble(a[0]);
            double num2 = Double.parseDouble(a[2]);
            char op = a[1].charAt(0);
            System.out.println("Step: this step, we are doing: " + num1 + op + num2);
            try {
                switch (op) {
                    case '+':
                        return num1 + num2;
                    case '-':
                        return num1 - num2;
                    case '*':
                        return num1 * num2;
                    case '/': {
                        if (num2 == 0) {
                            System.out.println("Error: divided 0!!");
                            System.exit(-1);
                        }
                        return num1 / num2;
                    }
                    case '%': {
                        if (num2 == 0) {
                            System.out.println("Error: divided 0!!");
                            System.exit(-1);
                        }
                        return num1 % num2;
                    }
                    default:
                        return -1;
                }
            } catch (Exception ex) {
                System.out.println("Error: the arithmetic you are doing is not valid, check again!");
                System.exit(-1);
            }
        }
        catch (Exception ex)
        {
            System.out.println("Error: in the expression, maybe you should write (-num) instead of -num...");
            System.exit(-1);
        }
        return -1;
    }
    public static boolean prior(String aa, String bb)
    {
        char a = aa.charAt(0);
        char b = bb.charAt(0);
        if((a == '*'||a == '/'||a == '%')&&(b == '+'||b == '-'))
            return true;
        return false;
    }
    public static double dealOne(String[] input)
    {
        if(input.length == 2)
            try {
                return Double.parseDouble(input[1]);
            }
            catch (Exception ex)
            {
                System.out.println("Error: the input should not be like this.. may be more numbers are needed!!");
                System.exit(-1);
            }
        //( 2):this condition
        else if(input.length == 3)                   //( -1):this condition
        {
            if(input[1].compareTo("-") == 0)
                return -Double.parseDouble(input[2]);
            else if(input[1].compareTo("+") == 0)
                return Double.parseDouble(input[2]);
        }
        else if(input.length == 1)
        {
            System.out.println("Error: there is an error.. maybe you should input symbols like'()'...");
            System.exit(-1);
        }
        Stack st = new Stack();
        String op = input[2];
        st.push(input[1]);      //the first number
        st.push(input[2]);      //the first number
        //st.push(input[3]);      //the first number
        try
        {
            st.push(input[3]);  // the second number
        }
        catch (Exception ex)
        {
            System.out.println("Error: missing a number!!");
            System.exit(-1);
            }
        int i = 4;
        if(input.length > 4) {
            try {
                while (true) {
                    if (prior(input[i], op) == false)//pop stack
                    {
                        String[] tmp = new String[3];
                        tmp[2] = st.pop().toString();
                        tmp[1] = st.pop().toString();
                        tmp[0] = st.pop().toString();
                        double resTmp = math(tmp);
                        st.push(resTmp);
                        op = input[i];
                        st.push(input[i]);
                        //st.push(input[i+1]);
                        try {
                            st.push(input[i + 1]);  // the second number
                        } catch (Exception ex) {
                            System.out.println("Error: missing a number!!");
                            System.exit(-1);
                        }
                        i += 2;
                        if (i >= input.length)
                            break;
                    } else if (prior(input[i], op) == true)  //pop self
                    {
                        String[] tmp = new String[3];
                        tmp[2] = input[i + 1];
                        tmp[1] = input[i];
                        tmp[0] = st.pop().toString();
                        double resTmp = math(tmp);
                        st.push(resTmp);
                        i += 2;
                        if (i >= input.length)
                            break;
                    }
                }
            }
            catch (Exception ex)
            {
                System.out.println("Error: there are some mistakes in the expression, check again!!!");
                System.exit(-1);
            }
        }
        String[] tmp = new String[3];
        tmp[2] = st.pop().toString();
        tmp[1] = st.pop().toString();
        tmp[0] = st.pop().toString();
        return math(tmp);
    }
    public static double dealExpression(String[] input)
    {
        ArrayList<String> tmpString = new ArrayList();
        tmpString.add(" ");
        int i, j = -1;
        //i is the count for input, j is the count for tmp result
        for(i = input.length-1; i >= 0; i--)
        {
            if(input[i].compareTo("(") != 0)
                continue;
            else
                break;
        }
        for(j = i+1; j < input.length; j++)
        {
            if(input[j].compareTo(")") != 0)
            {
                tmpString.add(input[j]);
                continue;
            }
            else
                break;
        }
        if(i != -1 && j == input.length)
        {
            System.out.println("Error: the brackets is not correct, missing ')'");
            System.exit(-1);
        }
        if(i == -1 && j != input.length)
        {
            System.out.println("Error: the brackets is not correct, missing '('");
            System.exit(-1);
        }
        if(i == -1 && j == input.length)
            return dealOne(input);
        String[] tmpInput = new String[tmpString.size()];//tmpString.split(" +");
        for(int k = 0; k < tmpString.size(); k++)
        {
            tmpInput[k] = tmpString.get(k);
        }
        double tmpResult = dealOne(tmpInput);
        tmpInput = new String[input.length - tmpInput.length];
        tmpInput[0] = " ";
        if(i != 1)
            System.arraycopy(input, 0, tmpInput, 0, i);

        tmpInput[i] = Double.toString(tmpResult);
        if(j != input.length-1)
            System.arraycopy(input, j+1, tmpInput, i+1, input.length - j - 1);
        input = tmpInput;

        return dealExpression(input);
    }
    public static void main(String args[])
    {
        Scanner in = new Scanner(System.in);
        while(true) {
            System.out.println(">>please enter a expression: ");
            String input = in.nextLine();
            String[] words = null;
            input = normalize(input);
            System.out.println("Step: the expression you input is: " + input);
            System.out.println("Check: all the input symbols are valid? " + checkSymbolsValid(input));
            if (!checkSymbolsValid(input)) {
                System.out.println("Error: the expression is not valid");
                System.exit(-1);
            }

            words = input.split(" +");
            double finalRes;
            try {
                finalRes = dealExpression(words);
                System.out.println(">>the result is: " + finalRes);
                System.out.println(">>the Integer result is: " + (int)finalRes);
            }
            catch (Exception ex)
            {
                System.out.println("Error: there is an error in the Expression!");
                System.out.println("Error: Please input the expression as standard as possible!!");
                System.exit(-1);
            }
        }
    }
}