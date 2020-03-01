package main;

import java.util.LinkedList;
import java.util.Queue;

public class Main {
	static Queue<Request> req = new LinkedList<>();
	static int queueMaxSize = 9;
	static int currentQueueCount = 0;


	public static void main(String[] args) {
		
		MainThread m = new MainThread();
		m.run();
		
	}

	
}
