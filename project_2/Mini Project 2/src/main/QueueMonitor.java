package main;

import java.util.LinkedList;
import java.util.Queue;
import java.util.locks.Lock;
import java.util.concurrent.Semaphore;

public static class QueueMonitor {

	Queue<Request> req = new LinkedList<Request>();
	Semaphore sem;
	Semaphore sem2 = new Semaphore(0);
	int bound;
	Lock lock = new Lock();
	
	public QueueMonitor(int size) {
		sem = new Semaphore(size);
	}
	
	public synchronized void add(Request r) {
		try {
			sem.acquire();
			lock.lock()
			req.add(r);
			lock.unlock();
			sem2.release();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public synchronized Request getNext() {
		try {
			sem2.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		sem.release();
		lock.lock()
		Request result = req.poll();
		lock.unlock();
		return result;
	}
	
	public synchronized boolean checkListEmpty() {
		if(req.isEmpty()) {
			return false;
		}else {
			return true;
		}
		
	}
}
