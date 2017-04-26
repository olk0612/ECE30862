package HW6;

public class D extends B implements I {

   public D( ) { };

   public void foo(int j) {}  // B: i is static final since i was declared in interface I

   public void foo(short s, D d,  double df) {System.out.println("D foo(short, D, double)");}

   public void bar(short s, D d,  double df) {System.out.println("D bar(short, D, double)");}

   public void dPrint( ) {
      System.out.println("i: "+i+", s: "+s);
   }
}
