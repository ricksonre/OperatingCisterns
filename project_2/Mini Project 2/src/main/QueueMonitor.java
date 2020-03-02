package main;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;

public class QueueMonitor {

	private Queue<Request> req = new LinkedList<Request>();
	private Semaphore processSemaphore;
	private Semaphore boundsSemaphore = new Semaphore(0);
	
	public QueueMonitor(int size) 
	{
		processSemaphore = new Semaphore(size);
	}
	
	public synchronized void add(Request r) 
	{
		try 
		{
			processSemaphore.acquire();
			
			req.add(r);
			
			boundsSemaphore.release();
		} 
		catch (InterruptedException e) 
		{
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
		processSemaphore.release();
		return req.poll();
		
	}
}
