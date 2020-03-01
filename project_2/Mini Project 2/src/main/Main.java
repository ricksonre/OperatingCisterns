package main;

import java.util.LinkedList;
import java.util.Queue;

public class Main {
	static Queue<Request> req = new LinkedList<>();
	static int queueMaxSize = 9;
	static int currentQueueCount = 0;
	static MainThread mt = new MainThread();

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		mt.run();
		
		
	}
	
	public static synchronized void addToQueue(Runnable r,Request req ){
		if(Main.currentQueueCount<Main.queueMaxSize) {
			Main.req.add(req);
			currentQueueCount++;
		}else {
			try {
				r.wait();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
	}

}
