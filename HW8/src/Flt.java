import java.lang.Float;

class Flt implements Comparable {

   Float f; // the value returned by the value method.

   public Flt(float f) {this.f = new Float(f);}

	@Override
	public double value() {
		return this.f.doubleValue();
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
