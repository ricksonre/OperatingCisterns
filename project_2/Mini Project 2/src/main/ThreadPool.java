package main;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;

public class ThreadPool extends Thread{
	Semaphore sem;
	
	
	
	public ThreadPool(int size) {
		sem = new Semaphore(size);
		
		
		
	}
	
	
	public void execute(final Runnable r) {
		
		
		try {
			sem.acquire();
			r.run();
			sem.release();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
		
		
	}
	
	

}
