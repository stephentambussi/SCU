class Uninit3
{
  public static void main(String[] arg)
  {
    int x=Integer.parseInt(arg[1]);
    int y;
    if (x > 0) 
      y=0;
    System.out.println(y);
  }
}
/*
    1:::::::::::::
      x=defined
      y=undefined
      (x>0)
    ::::::::::::::
        /     |
       /      |
      /       |
2:::::::::    |
  y=0         |
::::::::::    |
      \       |
       \      |
        \     |
    4:::::::::::::
      print(y)
    ::::::::::::::

Java output:
  error - variable y may have not been initialized
*/