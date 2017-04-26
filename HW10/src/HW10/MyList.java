package HW10;

public interface MyList extends Cloneable{
	public MyList next();
	public void printNode();
	public Object clone( ) throws java.lang.CloneNotSupportedException;
}
