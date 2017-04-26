public class IntegerArithmetic {
	public static Long add(Number op1, Number op2) throws Exception{
		if (op1 instanceof Long || op1 instanceof Integer && op2 instanceof Long || op2 instanceof Integer){
			long l1 = op1.longValue();
			long l2 = op2.longValue();
			return new Long(l1+l2);
		} else {
			Exception e = new Exception("Wrong input type");
			throw e;
		}
	}
	public static Long subtract(Number op1, Number op2) throws Exception{
		if (op1 instanceof Long || op1 instanceof Integer && op2 instanceof Long || op2 instanceof Integer){
			long l1 = op1.longValue();
			long l2 = op2.longValue();
			return new Long(l1-l2);
		} else {
			Exception e = new Exception("Wrong input type");
			throw e;
		}
	}
	public static Long multiply(Number op1, Number op2) throws Exception{
		if (op1 instanceof Long || op1 instanceof Integer && op2 instanceof Long || op2 instanceof Integer){
			long l1 = op1.longValue();
			long l2 = op2.longValue();
			return new Long(l1*l2);
		} else {
			Exception e = new Exception("Wrong input type");
			throw e;
		}
	}
	public static Long divide(Number op1, Number op2) throws Exception{
		if (op1 instanceof Long || op1 instanceof Integer && op2 instanceof Long || op2 instanceof Integer){
			long l1 = op1.longValue();
			long l2 = op2.longValue();
			if (l2 == 0){
				Exception e = new Exception("Divede by zero");
				throw e;
			} else {
				return new Long(l1+l2);
			}
		} else {
			Exception e = new Exception("Wrong input type");
			throw e;
		}
	}


}
