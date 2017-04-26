package HW5a;

class Main {

   public static void main(String args[]) {
      C0 c01 = new C0( );
      C0 c02 = new C0(1,2);
      C1 c11 = new C1( );
      C1 c12 = new C1(3, 4, 5.0f);

      System.out.println("c01.a.intValue( ): " + c01.a.intValue( ));
      System.out.println("c01.b.intValue( ): " + c01.b.intValue( ));
      System.out.println("c01.x: " + c01.x);
      System.out.println("c01.y: " + c01.y);

      System.out.println("c02.a.intValue( ): " + c02.a.intValue( ));
      System.out.println("c02.b.intValue( ): " + c02.b.intValue( ));
      System.out.println("c02.x: " + c02.x);
      System.out.println("c02.y: " + c02.y);

      System.out.println("c11.a.intValue( ): " + c11.a.intValue( ));
      System.out.println("c11.b.intValue( ): " + c11.b.intValue( ));
      System.out.println("c11.c.floatValue( ): " + c11.c.floatValue( ));
      System.out.println("c11.x: " + c11.x);
      System.out.println("c11.y: " + c11.y);
      System.out.println("c11.z: " + c11.z);

      c01 = c12;
      System.out.println("c12.a.intValue( ): " + c01.a.intValue( ));
      System.out.println("c12.b.intValue( ): " + c01.b.intValue( ));
      System.out.println("c12.c.floatValue( ): " + ((C1) c01).c.floatValue( ));
      System.out.println("c12.x: " + c01.x);
      System.out.println("c12.y: " + c01.y);
      //System.out.println("c12.z: " + c01.z);

      System.out.println("c02.getA( ): " + c02.getA( ));
      System.out.println("c02.getB( ): " + c02.getB( ));
      System.out.println("c02.getX( ): " + c02.getX( ));
      System.out.println("c02.getY( ): " + c02.getY( ));

      System.out.println("c12.getA( ): " + c01.getA( ));
      System.out.println("c12.getB( ): " + c01.getB( ));
      System.out.println("c12.getC( ): " + ((C1) c01).getC( ));
      System.out.println("c12.getX( ): " + c01.getX( ));
      System.out.println("c01.getY( ): " + c01.getY( ));
      System.out.println("c01.getZ( ): " + c01.getY( ));
      /*
      c01.a.intValue( ): 0
      c01.b.intValue( ): 0
      c01.x: 0
      c01.y: 0
      c02.a.intValue( ): 1
      c02.b.intValue( ): 2
      c02.x: 1
      c02.y: 2
      c11.a.intValue( ): 0
      c11.b.intValue( ): 0
      c11.c.floatValue( ): 1.5
      c11.x: 0
      c11.y: 0
      c11.z: 1.5
      c12.a.intValue( ): 3
      c12.b.intValue( ): 4
      c12.c.floatValue( ): 5.0
      c12.x: 0
      c12.y: 0
      c02.getA( ): -1
      c02.getB( ): -2
      c02.getX( ): -1
      c02.getY( ): -2
      c12.getA( ): -3
      c12.getB( ): -4
      c12.getC( ): 5.0
      c12.getX( ): 0
      c01.getY( ): 1
      c01.getZ( ): 1
       */
   }
}
