class Uninit2
{
  public static void main(String[] arg)
  {
    int x=Integer.parseInt(arg[1]);
    int y;
    if (x > 0) 
      y=0;
    else {
      y=1;
    }
    System.out.println(y);
  }
}
/*
    1:::::::::::::
      x=defined
      y=undefined
      (x>0)
    ::::::::::::::
        /   \
       /     \
      /       \
2:::::::::   3:::::::::
  y=0          y=1
::::::::::    ::::::::::
      \       /
       \     /
        \   /
    4:::::::::::::
      print(y)
    ::::::::::::::

Java output:
  compiles without warning
*/