package lab8exer4;

public class StringManager {

	public boolean palindrome(String og)
	{
		String lineInLowerCase = og.replaceAll("\\s+", "").toLowerCase();
		StringBuffer line = new StringBuffer(lineInLowerCase);
		StringBuffer reverse = line.reverse();
		return (reverse.toString()).equals(lineInLowerCase);
	}
	
	public int getNoOfWords(String lineOfText)
	{
		String[] words = lineOfText.split("\\s+");
		return words.length;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
}
