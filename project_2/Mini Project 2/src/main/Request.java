package main;


//This class represents the Requests produced by the main thread to simulate activity
public class Request implements Runnable {
	public static int requestID;
	int ID;
	int length;//declare class vars
	
	public Request(int maxDur) //constructor
	{
		this.ID = Request.requestID++;//initialize vars to required vals
		this.length = maxDur;
		
	}
	
	public int getID() {//getId method, returns the request ID
		return ID;
	}

	@Override
	public void run() //main running function to run a thread
	{
		
		try 
		{
			Thread.sleep(100);
			System.out.println("Task "+ID+" running @ time " + System.currentTimeMillis());
			Thread.sleep(length);
			System.out.println("Task "+ID+" complete " + + System.currentTimeMillis());
			//sleep and print what you are doing, sleep for request length
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}
		
	}

}
