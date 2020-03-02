package main;

import java.util.LinkedList;
import java.util.Queue;
import java.util.locks.Lock;
import java.util.concurrent.Semaphore;

public class QueueMonitor {

	private Queue<Request> req = new LinkedList<Request>();
	private Semaphore processSemaphore;
	private Semaphore boundsSemaphore = new Semaphore(0);
	Lock lock = new Lock();

	public QueueMonitor(int size)
	{
		processSemaphore = new Semaphore(size);
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

	public synchronized Request getNext()
	{
		try
		{
			boundsSemaphore.acquire();
		}
		catch (InterruptedException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		sem.release();
		lock.lock()
		Request result = req.poll();
		lock.unlock();
		return result;
	}
}
