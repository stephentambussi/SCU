class Uninit
{
  public static void main(String[] arg)
  {
    int x=Integer.parseInt(arg[1]);
    int y;
    if (x > 0) 
      System.out.println(y);
    else {
      y=1;
      System.out.println(y);
    }
  }
}
/*
    1:::::::::::::
      x=defined
      y=undefined
      (x>0)
    ::::::::::::::
       /  \
      /    \
     /      \
2:::::::::   3:::::::::
  print(y)     y=1
:::::::::      print(y)
             ::::::::::

Java output:
  error - variable y may have not been initialized
*/