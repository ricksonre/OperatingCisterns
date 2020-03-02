package main;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;

public class QueueMonitor {

	Queue<Request> req = new LinkedList<Request>();
	Semaphore sem;
	Semaphore sem2 = new Semaphore(0);
	int bound;
	
	public QueueMonitor(int size) {
		sem = new Semaphore(size);
	}
	
	public synchronized void add(Request r) {
		try {
			System.out.println("AQadd");
			sem.acquire();
			
			req.add(r);
			
			sem2.release();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public synchronized Request getNext() {
		try {
			System.out.println("AQrem");
			sem2.acquire();
			System.out.println("sem2Aqed");
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		sem.release();
		System.out.println("sem1Released");
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
