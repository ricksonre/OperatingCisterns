package main;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;

public class ThreadPool{
	Semaphore sem;
	ExecutorService exe;
	
	
	public ThreadPool(int size) {
		sem = new Semaphore(size);
		exe = Executors.newFixedThreadPool(size);
		
		
	}
	
	
	public void execute(final Runnable r) {
		
		
		try {
			sem.acquire();
			
			exe.execute(r);
			sem.release();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
		
		
	}


	
	
	

}
