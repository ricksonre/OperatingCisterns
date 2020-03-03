package main;


//This class represents the Requests produced by the main thread to simulate activity
public class Request implements Runnable {
	public static int requestID;
	int ID;
	int length;
	
	public Request(int maxDur) 
	{
		this.ID = Request.requestID++;
		this.length = maxDur;
		
	}
	
	public int getID() {
		return ID;
	}

	@Override
	public void run() 
	{
		
		try 
		{
			Thread.sleep(100);
			System.out.println("Task "+ID+" running");
			Thread.sleep(length);
			System.out.println("Task "+ID+" complete");
		} 
		catch (InterruptedException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
