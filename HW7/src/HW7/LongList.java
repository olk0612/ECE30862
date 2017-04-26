package HW7;

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
}
