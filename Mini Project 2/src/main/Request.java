package main;

import java.util.Random;

public class Request {
	static int requestID;
	int ID;
	int length;
	
	public Request(int maxDur) {
		Random r = new Random();
		this.ID = Request.requestID++;
		this.length = r.nextInt(maxDur);
		
	}

}
