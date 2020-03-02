package main;

import java.util.Queue;
import java.util.concurrent.Executor;


public class SlaveThread extends Thread {
	boolean running = false;
	static int SlaveID;
	int ID;
	QueueMonitor q;
	

	public SlaveThread(QueueMonitor queue) {
		this.q = queue;
		this.ID = SlaveThread.SlaveID++;
	}

	public void run() {
		while (true) {
			Request r = q.getNext();
			System.out.println("Slave thread "+ID+" is running ");
			new Thread(r).start();
			
		}
	}

}
