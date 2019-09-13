import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	
	static Scanner cin=new Scanner(System.in);
	static String a;
	static BigInteger ZERO=BigInteger.valueOf(0);
	static BigInteger ONE=BigInteger.valueOf(1);
	static BigInteger TWO=BigInteger.valueOf(2);
	static BigInteger Four=BigInteger.valueOf(4);
	public static void main(String[] args) {
		
		a=cin.next();
		BigInteger s=ZERO;
		
		int k=a.length()-1;
		for(int i=0;i < a.length();++i) {
			
			BigInteger base=ONE;
			for(int j=1;j <= k;++j)//2^k求解
				base=base.multiply(TWO);
			
			if(a.charAt(i) == '1' ? true:false)
				s=s.add(base);
			
			k--;
		}

		int ans=0;
		BigInteger base=ONE;
		for(;base.compareTo(s) == -1 ? true:false;ans++)
			base=base.multiply(BigInteger.valueOf(4));
		
		System.out.println(ans);
	}
}
