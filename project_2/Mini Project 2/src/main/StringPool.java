package main;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.locks.Lock;

public class StringPool {
	Lock[] lk;
	Thread[] tp;
	Queue<Thread> q = new LinkedList<>();
	
	
	public StringPool(int size) {
		tp = new Thread[size];
		lk = new Lock[size];
		
	}
	
	
	public synchronized void runTask(Runnable r) {
		
		
		
	}
	
	private synchronized int findOpenLock() {
		for(int i = 0; i< lk.length; i++) {
			if(lk[i].tryLock()) {
				return i;
			}
		}
		return -1;
	}

}
