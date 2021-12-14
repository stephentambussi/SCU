package lab8;

public class MyCalculator {

	public int add(int i, int j)
	{
		return i+j;
	}
	
	public int subtract(int i, int j)
	{
		return i-j;
	}
	
	public int multiply(int i, int j)
	{
		return i*j;
	}
	
	public int divide(int i, int j)
	{
		if(j == 0)
			throw new java.lang.Error("Cannot divide by zero");
		return (i / j);
	}
	
	public int mod(int i, int j)
	{
		if(j == 0)
			throw new java.lang.Error("Cannot divide by zero");
		return (i % j);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
}
