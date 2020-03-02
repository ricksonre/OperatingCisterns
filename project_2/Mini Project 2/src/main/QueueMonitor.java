package main;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;

public class QueueMonitor 
{

	private Queue<Request> req = new LinkedList<Request>();
	private Semaphore processSemaphore;
	private Semaphore boundsSemaphore;

	public QueueMonitor(int size)
	{
		boundsSemaphore = new Semaphore(size);
		processSemaphore = new Semaphore(0);
	}

	public synchronized void add(Request r) 
	{
		try 
		{
			boundsSemaphore.acquire();
			
			req.add(r);
			
			processSemaphore.release();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}

	}

	public synchronized Request getNext()
	{
		try
		{
			processSemaphore.acquire();
		}
		catch (InterruptedException e)
		{
			e.printStackTrace();
		}
		boundsSemaphore.release();
		Request result = req.poll();
		return result;
	}
}
