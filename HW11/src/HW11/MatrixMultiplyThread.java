package hw11;

public class MatrixMultiplyThread extends Thread{
	private MatrixMultiply mm;
	private int x1, x2, y1, y2;
	
	public MatrixMultiplyThread(MatrixMultiply mm, int x1, int x2, int y1, int y2) {
		this.mm = mm;
		this.x1 = x1;
		this.x2 = x2;
		this.y1 = y1;
		this.y2 = y2;
	}
	
	public void run() {
		this.mm.multiply(this.x1,this.x2,this.y1,this.y2);
	}
}
