package HW7;

public class IntList implements MyList{
	private int data;
	private IntList next;
	public IntList(int data){
		this.data = data;
	}
	public IntList(IntList n, int data){
		this.data = data;
		this.next = n;
	}
	public int getData(){
		return this.data;
	}
	public IntList next(){
		return this.next;
	}
	public void printNode(){
		System.out.print("IntList Node, data is: "+this.data);
	}
}
