package lab8exer4;

import static org.junit.Assert.*;

import org.junit.Test;

public class StringManagerTest {

	@Test
	public void testPalindrome() {
		StringManager sm = new StringManager();
		boolean result = sm.palindrome("racecar");
		//compare the expected result with the actual
		assertEquals(true, result);
	}

	@Test
	public void testGetNoOfWords() {
		StringManager sm = new StringManager();
		int result = sm.getNoOfWords("Hello World! My name is Stephen.");
		//compare the expected result with the actual
		assertEquals(6, result);
	}

}
