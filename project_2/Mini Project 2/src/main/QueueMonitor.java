package main;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;

//main monitor for controlling the queue
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
			//Aquire semaphore to bet queue space
			boundsSemaphore.acquire();
			notify();
			
			
			req.add(r);
			//Release sephore to indicate queue is not empty
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
			//Release lock if queue is empty
			if(req.isEmpty()) {
				wait();
			}
			//Aquire semaphore to aquire request
			processSemaphore.acquire();
		}
		catch (InterruptedException e)
		{
			e.printStackTrace();
		}

		//release semaphore
		boundsSemaphore.release();
		Request result = req.poll();
		return result;
	}
}
