package main;

import java.util.Random;

public class Request implements Runnable {
	static int requestID;
	int ID;
	int length;
	
	public Request(int maxDur) {
		Random r = new Random();
		this.ID = Request.requestID++;
		this.length = r.nextInt(maxDur);
		
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			System.out.println("Starting task" + ID);
			Thread.sleep(length);
			System.out.println("Completed task" + ID);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
