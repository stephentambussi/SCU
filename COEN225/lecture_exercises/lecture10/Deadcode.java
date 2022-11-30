class Deadcode
{
  public static void main(String[] arg)
  {
    int x=Integer.parseInt(arg[1]);
    if (x > 0) 
      return;
    else
      return;
    System.out.println(x);
  }
}
/*
    1:::::::::::::
      x=defined
      (x>0)
    ::::::::::::::
       /  \
      /    \
     /      \
2:::::::::   3:::::::::
  return       return
:::::::::    ::::::::::

   4::::::::::
     println()
   :::::::::::

Java output:
  error - unreachable statement
*/