package main;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class QueueMonitor {
	
	Queue<Request> req = new LinkedList<Request>();
	
	
	
	public synchronized void add(Request r) {
		req.add(r);
	}
	
	public synchronized Runnable getNext() {
		return req.poll();
		
	}
	
	public synchronized boolean checkListEmpty() {
		if(req.isEmpty()) {
			return false;
		}else {
			return true;
		}
		
	}
}
