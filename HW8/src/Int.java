import java.lang.Integer;

class Int implements Comparable {

   Integer i;

   public Int(int j) {i = new Integer(j);}

   @Override
   public double value() {
	   return this.i.doubleValue();
   }

   @Override
   public boolean lessThan(Comparable c) {
	   return this.value() < c.value();
   }

   @Override
   public boolean equal(Comparable c) {
	   return this.value() == c.value();
   }

   @Override
   public boolean greaterThan(Comparable c) {
	   return this.value() > c.value();
   }

}
