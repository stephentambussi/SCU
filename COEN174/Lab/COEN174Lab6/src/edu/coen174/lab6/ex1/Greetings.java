package edu.coen174.lab6.ex1;
import java.util.Scanner;
import java.time.LocalDate;
import java.time.LocalDateTime;

public class Greetings {
	public static void main(String[] args)
	{
		// Display Greetings on running the program
		System.out.println("Hello World!");
		String name = getInputFromUser();
		System.out.println("Hello " + name);
		GreetingsGenerator.sendGreetings(name);
	}
	public static String getInputFromUser()
	{
		Scanner in = new Scanner(System.in);
		System.out.println("Enter your Name: ");
		String name = in.nextLine();
		return name;
	}
}

class GreetingsGenerator {
	public static void sendGreetings(String name)
	{
		// This gets the hour of current time of day
		int hour = LocalDateTime.now().getHour();
		String morning = "Good Morning";
		String evening = "Good Evening";
		String night = "Good Night";
		if (hour >= 1 && hour <= 12)
			System.out.println(morning + " " + name);
		else if (hour > 12 && hour <= 18)
			System.out.println(evening + " " + name);
		else if (hour > 18 && hour <= 23)
			System.out.println(night + " " + name);
	}
}
