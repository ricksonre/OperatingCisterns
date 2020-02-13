package main;

import java.util.LinkedList;
import java.util.Queue;

public class Main {
	static Queue<Request> req = new LinkedList<>();
	static int queueMaxSize = 9;
	static int currentQueueCount = 0;

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MainThread mt = new MainThread();
		mt.run();
		
		
	}
	
	public synchronized void addToQueue(Runnable r,Request req ){
		
		
	}

}
