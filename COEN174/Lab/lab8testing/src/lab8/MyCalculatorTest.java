package lab8;

import static org.junit.Assert.*;

import org.junit.Test;

public class MyCalculatorTest {

	@Test
	public void testAdd() {
		MyCalculator calculator = new MyCalculator();
		int result = calculator.add(100, 200);
		//compare the expected result with the actual
		assertEquals(300, result);
	}

	@Test
	public void testSubtract() {
		MyCalculator calculator = new MyCalculator();
		int result = calculator.subtract(100, 200);
		//compare the expected result with the actual
		assertEquals(-100, result);
	}

	@Test
	public void testMultiply() {
		MyCalculator calculator = new MyCalculator();
		int result = calculator.multiply(100, 200);
		//compare the expected result with the actual
		assertEquals(20000, result);
	}
	
	@Test
	public void testDivide() {
		MyCalculator calculator = new MyCalculator();
		int result = calculator.divide(200, 10);
		//compare the expected result with the actual
		assertEquals(20, result);
	}
	
	@Test
	public void testMod() {
		MyCalculator calculator = new MyCalculator();
		int result = calculator.mod(100, 10);
		//compare the expected result with the actual
		assertEquals(0, result);
	}
}
