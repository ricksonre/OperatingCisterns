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
		System.out.println("me try but fail");
		try 
		{
			boundsSemaphore.acquire();
			notify();
			System.out.println("me cry");
			
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
			if(req.isEmpty()) {
				wait();
			}
			System.out.println("meme");
			processSemaphore.acquire();
		}
		catch (InterruptedException e)
		{
			e.printStackTrace();
		}
		System.out.println("me cry");
		boundsSemaphore.release();
		Request result = req.poll();
		return result;
	}
}
