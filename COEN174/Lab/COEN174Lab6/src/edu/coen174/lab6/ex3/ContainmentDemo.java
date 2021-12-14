package edu.coen174.lab3.ex3;

class One {
	private String varOne;
	private static int id = 0;
	
	public One(String varOne)
	{
		this.varOne = varOne;
		++id;
	}
	public One()
	{
		this.varOne = "varOne Not Set";
	}
	public void show()
	{
		System.out.println("[One-ID:"+id);
		System.out.println(varOne);
		System.out.println(" ]");
	}
	public void change(String s)
	{
		varOne = s;
	}
}
class Two
{
	private One one;
	private static int id = 0;
	public Two(One one)
	{
		this.one = one;
		++id;
	}
	public void show()
	{
		System.out.println("[Two-Id:"+id);
		one.show();
		System.out.println("Two]");
	}
}
class Three
{
	private One one;
	public Three(String param)
	{
		one = new One(param);
	}
	public void show()
	{
		System.out.println("[Three ");
		one.show();
		System.out.println("Three]");
	}
}
class Four
{
	private One one;
	public Four(One param)
	{
		one = param;
	}
	public void show()
	{
		System.out.println("[Four:");
		one.show();
		System.out.println("Four]");
	}
	public void modify(String s)
	{
		one.change(s);
	}
}
public class ContainmentDemo
{
	public static void main(String [] args)
	{
		One a1 = new One(new String("Hello"));
		
		//Create an instance of Two with an instance of One
		Two b1 = new Two(a1);
		b1.show();
		
		Two b2 = new Two(a1);
		b2.show();
		
		a1.change("Goodbye");
		b1.show();
		b2.show();
		
		Four f1 = new Four(a1);
		f1.show();
		f1.modify("Having fun?");
		f1.show();
		b1.show();
		b2.show();
		
		Three t1 = new Three(new String("HI"));
		t1.show();
		
	}
}
