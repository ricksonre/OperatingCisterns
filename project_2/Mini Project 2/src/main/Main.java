package main;

import java.util.Scanner;

public class Main 
{

	public static void main(String[] args) 
	{
		//Obtain input values
		int numberSlaves,max;
		Scanner scanner = new Scanner(System.in);
	    System.out.println("Enter the number of threads and size of the bounded buffer: ");
	    numberSlaves = scanner.nextInt();
	    System.out.println("Enter the maximum process length and sleep time: ");
	    max = scanner.nextInt();
	    //Creation and start of master thread
		MainThread master = new MainThread(numberSlaves,max);
		master.start();
		scanner.close();
		
	}

	
}
