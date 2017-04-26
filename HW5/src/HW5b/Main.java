package HW5b;
class Main {

   public static void main(String args[]) {
      char c = 0;
      short s = 1;
      int i = 2;
      float f = 0.0f;
      double df = 1.0;

      B b = new B( );
      D d = new D( );

      System.out.println("Direct calls");
      //d.foo(d, f); 
      //d.foo(c, d, df);
      d.foo(df); 
      d.foo(i); 
      //d.foo( );
      //d.foo(i, d, df);
      d.foo(c, b, f); 
      d.foo(f); 
      d.foo(c); 
      d.foo(s, d, df); 
      //d.foo(i, d);

      System.out.println("b.caller");
      b.caller( );
      /*
       * Direct calls
		 B:foo(double)
		 D:foo(float)
		 D:foo(int, B, float)
		 D:foo(float)
		 D:foo(float)
		 B:foo(short, B, double)
		 b.caller
		 B:foo(short)
		 B:foo(double)
       */

   }
}
