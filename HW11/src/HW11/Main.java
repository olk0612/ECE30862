package hw11;
import java.util.Scanner;
public class Main {
	public static void main( String[] args ) {
		while(true){
			try {
				System.out.println("Please enter size N");
				Scanner in = new Scanner(System.in);
				int size = in.nextInt();
				MatrixMultiply mm = new MatrixMultiply(size);
				mm.fill();
				
				long currTime = System.currentTimeMillis();
				mm.multiply(0,size,0, size);
				System.out.println("Single Thread Runtime: " + (System.currentTimeMillis() - currTime));
				

				MatrixMultiplyThread t1 = new MatrixMultiplyThread(mm,0,size,0,size/2);
				MatrixMultiplyThread t2 = new MatrixMultiplyThread(mm,0,size,size/2,size);
				currTime = System.currentTimeMillis();
				t1.run();
				t2.run();
				System.out.println("Two Threads Runtime: " + (System.currentTimeMillis() - currTime));
				

				MatrixMultiplyThread ta = new MatrixMultiplyThread(mm,0,size/2,0,size/2);
				MatrixMultiplyThread tb = new MatrixMultiplyThread(mm,size/2,size,size/2,size);
				MatrixMultiplyThread tc = new MatrixMultiplyThread(mm,0,size/2,0,size/2);
				MatrixMultiplyThread td = new MatrixMultiplyThread(mm,size/2,size,size/2,size);
				currTime = System.currentTimeMillis();
				ta.run();
				tb.run();
				tc.run();
				td.run();
				System.out.println("Four Threads Runtime: " + (System.currentTimeMillis() - currTime));
				break;
			} catch(IllegalArgumentException e){
				System.out.println(e.getLocalizedMessage());
			}
				
		}
	}

}
