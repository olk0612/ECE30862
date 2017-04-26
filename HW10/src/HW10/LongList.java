package HW10;

public class LongList implements MyList {
	private long data;
	private LongList next;
	
	public LongList(long data){
		this.data = data;
	}
	public LongList(LongList n, long data){
		this.data = data;
		this.next = n;
	}
	public long getData(){
		return this.data;
	}
	public LongList next(){
		return this.next;
	}
	public void printNode(){
		System.out.print("LongList Node, data is: "+this.data);
	}
	public Object clone( ) throws java.lang.CloneNotSupportedException {

	      LongList node = (LongList) super.clone( );
	      if (this.next( ) != null) {
	         node.next = (LongList) this.next( ).clone( );
	      } else {
	         node.next = null;
	      }
	      node.data = -node.data; 

	      return node;
	   }
}
