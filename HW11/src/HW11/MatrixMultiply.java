package hw11;

import java.util.Random;

class MatrixMultiply {
	private int[][] matrixA = null;
	private int[][] matrixB = null;
	private int[][] matrixC = null;
	private int size;
	
	public MatrixMultiply(int size){
		this.size = size;
	}
	
	public void setSize(int size) {
		this.size = size;
	}
	public int getSize() {
		return size;
	}
	
	public void fill() throws IllegalArgumentException{
		Random r = new Random();
		if (this.size % 2 != 0){
			throw new IllegalArgumentException("N is " + this.size + ". N must be even");
		}
		this.matrixB = new int[this.size][this.size];
		this.matrixC = new int[this.size][this.size];
		this.matrixA = new int[this.size][this.size];
		for (int i = 0; i < this.size; i++) {
			for ( int j = 0; j < this.size; j++){
				this.matrixB[i][j] = r.nextInt(10);
				this.matrixC[i][j] = r.nextInt(10);
				this.matrixA[i][j] = 0;
			}
		}
	}
	public void multiply (int x1, int x2, int y1, int y2) {
	    
    	for (int i = x1; i < x2; i++) { 
            for (int j = y1; j < y2; j++) { 
                for (int k = 0; k < this.size; k++) { 
                	this.matrixA[i][j] = this.matrixA[i][j] + this.matrixB[k][j] * this.matrixC[i][k];
                }
            }
        }
  	
    }
	
	
    
}
