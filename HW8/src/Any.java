// A simple demonstration of the existence of the Object class 
// and the hashCode method defined by the Object class.
class Any extends Object implements Comparable {

   final double value;

   public Any( ) {
      value = hashCode( );
   }

	@Override
	public double value() {
		return this.value;
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
